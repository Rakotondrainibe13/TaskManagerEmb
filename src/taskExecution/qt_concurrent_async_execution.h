#pragma once

#include "iasync_task_execution.h"
#include <QtConcurrent>
#include <QFuture>
#include <QString>
#include <QFutureWatcher>
#include <QObject>

namespace TaskExecution{
    class QtConcurrentAsyncExecution : public AsyncTaskExecution {
    public:
        explicit QtConcurrentAsyncExecution(std::function<void()> task);
        void start() override;
        void pause() override;
        void resume() override;
        void cancel() override;
        QString getStatus() const override { return m_status; }
        int getProgress() const override { return m_progress; }

    private:
        QFuture<void> m_future;
        QFutureWatcher<void> m_watcher;
        std::function<void()> m_task;

        void handleFinished();
    };
}
