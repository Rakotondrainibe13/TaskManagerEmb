#include "timer_based_async_execution.h"

namespace TaskExecution{
    TimerBasedAsyncExecution::TimerBasedAsyncExecution(std::function<void()> task, int interval)
        : m_task(task) {
        m_timer.setInterval(interval);
    }

    void TimerBasedAsyncExecution::start() {
        if (m_status == "NotStarted") {
            connect(&m_timer, &QTimer::timeout, this, &TimerBasedAsyncExecution::executeTask);
            m_timer.start();
            m_status = "Running";
            emit taskStarted();
        }
    }

    void TimerBasedAsyncExecution::pause() {
        if (m_status == "Running") {
            m_timer.stop();
            m_status = "Paused";
            emit taskPaused();
        }
    }

    void TimerBasedAsyncExecution::resume() {
        if (m_status == "Paused") {
            m_timer.start();
            m_status = "Running";
            emit taskResumed();
        }
    }

    void TimerBasedAsyncExecution::cancel() {
        if (m_status == "Running" || m_status == "Paused") {
            m_timer.stop();
            m_status = "Cancelled";
            emit taskCancelled();
        }
    }

    void TimerBasedAsyncExecution::executeTask() {
        try {
            m_task();
            emit progressUpdated(++m_progress);
        } catch (const std::exception& e) {
            emit taskFailed(QString::fromStdString(e.what()));
            m_timer.stop();
        }
    }
}
