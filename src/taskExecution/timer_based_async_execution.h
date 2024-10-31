#pragma once

#include "iasync_task_execution.h"
#include <QTimer>
#include <QString>
#include <QObject>

namespace TaskExecution{
    class TimerBasedAsyncExecution :public AsyncTaskExecution {
    public:
        explicit TimerBasedAsyncExecution(QObject * parent = nullptr);
        TimerBasedAsyncExecution(std::function<void()> task, int interval);
        void start() override;
        void pause() override;
        void resume() override;
        void cancel() override;
        QString getStatus() const override { return m_status; }
        int getProgress() const override { return m_progress; }

    private:
        QTimer m_timer;
        std::function<void()> m_task;

        void executeTask();
    };
}
