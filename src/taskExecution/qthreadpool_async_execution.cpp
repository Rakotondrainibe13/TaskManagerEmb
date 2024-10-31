#include "qthreadpool_async_execution.h"
#include <QThreadPool>

namespace TaskExecution{
    QThreadPoolAsyncExecution::QThreadPoolAsyncExecution(std::function<void()> task)
        : m_task(task) {}

    void QThreadPoolAsyncExecution::start() {
        if (m_status == "NotStarted") {
            m_status = "Running";
            QThreadPool::globalInstance()->start(this);
            emit taskStarted();
        }
    }

    void QThreadPoolAsyncExecution::run() {
        try {
            m_task();
            if (!m_isCancelled) {
                m_status = "Completed";
                emit taskCompleted();
            }
        } catch (const std::exception& e) {
            emit taskFailed(QString::fromStdString(e.what()));
        }
    }

    void QThreadPoolAsyncExecution::pause() {
        QMutexLocker locker(&m_mutex);
        if (m_status == "Running") {
            m_isPaused = true;
            m_status = "Paused";
            emit taskPaused();
        }
    }

    void QThreadPoolAsyncExecution::resume() {
        QMutexLocker locker(&m_mutex);
        if (m_status == "Paused") {
            m_isPaused = false;
            m_status = "Running";
            m_pauseCondition.wakeAll();
            emit taskResumed();
        }
    }

    void QThreadPoolAsyncExecution::cancel() {
        QMutexLocker locker(&m_mutex);
        if (m_status == "Running" || m_status == "Paused") {
            m_isCancelled = true;
            m_status = "Cancelled";
            emit taskCancelled();
        }
    }
}
