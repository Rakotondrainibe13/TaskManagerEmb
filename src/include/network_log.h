#pragma once

#include <QDateTime>
#include <QString>

class NetworkLog {
public:
    NetworkLog();
    NetworkLog(const QDateTime& timestamp, const QString& server, const QString& status, const QString& response);

    // Getters
    QDateTime getTimestamp() const;
    QString getServer() const;
    QString getStatus() const;
    QString getResponse() const;

    // Setters
    void setTimestamp(const QDateTime& timestamp);
    void setServer(const QString& server);
    void setStatus(const QString& status);
    void setResponse(const QString& response);

private:
    QDateTime timestamp;
    QString server;
    QString status;
    QString response;
};
