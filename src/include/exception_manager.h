#ifndef EXCEPTION_MANAGER_H
#define EXCEPTION_MANAGER_H

#include <QException>
#include <QString>

class ExceptionManager : public QException
{
public:
    ExceptionManager(const QString &message) : m_message(message) {}

    void raise() const override { throw *this; }
    ExceptionManager *clone() const override { return new ExceptionManager(*this); }

    QString message() const { return m_message; }

private:
    QString m_message;
};

#endif 
