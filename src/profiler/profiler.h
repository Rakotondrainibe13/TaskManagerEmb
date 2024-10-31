#ifndef PROFILER_H
#define PROFILER_H

#include <QString>
#include <QElapsedTimer>

namespace Profiler{
class Profiler{
public:
    Profiler(const QString& functionName);
    ~Profiler();
private:
    QElapsedTimer m_timer;
    QString m_functionName;
};
}

#endif // PROFILER_H
