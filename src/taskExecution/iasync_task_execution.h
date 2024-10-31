#pragma once
#include<QString>
#include <QObject>

namespace TaskExecution{
  class AsyncTaskExecution: public QObject {
    Q_OBJECT
    public:
        virtual ~AsyncTaskExecution() = default;
        virtual void start() = 0;
        virtual void pause() = 0;
        virtual void resume() = 0;
        virtual void cancel() = 0;
        virtual QString getStatus() const = 0;
        virtual int getProgress() const = 0;

    signals:
        void taskStarted();
        void taskPaused();
        void taskResumed();
        void taskCancelled();
        void taskCompleted();
        void taskFailed(const QString& error);
        void progressUpdated(int progress);

    protected:
        QString m_status = "NotStarted";
        int m_progress = 0;
    };
}
