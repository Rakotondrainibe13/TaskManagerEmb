#pragma once

#include "iasync_task_execution.h"
#include <QRunnable>
#include <QMutex>
#include <QWaitCondition>
#include <QObject>

namespace TaskExecution{
class QThreadPoolAsyncExecution : public AsyncTaskExecution, public QRunnable {
    public:
        explicit QThreadPoolAsyncExecution(std::function<void()> task);
        void start() override;
        void pause() override;
        void resume() override;
        void cancel() override;
        QString getStatus() const override { return m_status; }
        int getProgress() const override { return m_progress; }

    protected:
        void run() override;

    private:
        std::function<void()> m_task;
        QMutex m_mutex;
        QWaitCondition m_pauseCondition;
        bool m_isPaused = false;
        bool m_isCancelled = false;
    };
}
