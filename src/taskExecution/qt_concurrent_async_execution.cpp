#include "qt_concurrent_async_execution.h"

namespace TaskExecution{
    QtConcurrentAsyncExecution::QtConcurrentAsyncExecution(std::function<void()> task)
        : m_task(task) {}

    void QtConcurrentAsyncExecution::start() {
        if (m_status == "NotStarted") {
            m_future = QtConcurrent::run(m_task);
            m_watcher.setFuture(m_future);
            connect(&m_watcher, &QFutureWatcher<void>::finished, this, &QtConcurrentAsyncExecution::handleFinished);
            m_status = "Running";
            emit taskStarted();
        }
    }

    void QtConcurrentAsyncExecution::pause() {
        if (m_status == "Running") {
            // Simulate pause (not natively supported in QtConcurrent)
            m_status = "Paused";
            emit taskPaused();
        }
    }

    void QtConcurrentAsyncExecution::resume() {
        if (m_status == "Paused") {
            // Simulate resume (not natively supported in QtConcurrent)
            m_status = "Running";
            emit taskResumed();
        }
    }

    void QtConcurrentAsyncExecution::cancel() {
        if (m_status == "Running" || m_status == "Paused") {
            m_future.cancel();
            m_status = "Cancelled";
            emit taskCancelled();
        }
    }

    void QtConcurrentAsyncExecution::handleFinished() {
        if (m_status != "Cancelled") {
            m_status = "Completed";
            emit taskCompleted();
        }
    }
}
