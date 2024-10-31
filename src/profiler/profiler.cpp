#include "profiler.h"
#include <QDebug>

namespace Profiler{

Profiler::Profiler(const QString& functionName) : m_functionName(functionName) {
    m_timer.start();
}
Profiler::~Profiler() {
    qDebug() << m_functionName << "took" << m_timer.elapsed() << "ms";
}

}
