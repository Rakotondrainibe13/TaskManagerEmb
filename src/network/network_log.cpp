#include "../include/network_log.h"

// Constructeurs
NetworkLog::NetworkLog() {}

NetworkLog::NetworkLog(const QDateTime& timestamp, const QString& server, const QString& status, const QString& response)
    : timestamp(timestamp), server(server), status(status), response(response) {}

// Getters
QDateTime NetworkLog::getTimestamp() const {
    return timestamp;
}

QString NetworkLog::getServer() const {
    return server;
}

QString NetworkLog::getStatus() const {
    return status;
}

QString NetworkLog::getResponse() const {
    return response;
}

// Setters
void NetworkLog::setTimestamp(const QDateTime& timestamp) {
    this->timestamp = timestamp;
}

void NetworkLog::setServer(const QString& server) {
    this->server = server;
}

void NetworkLog::setStatus(const QString& status) {
    this->status = status;
}

void NetworkLog::setResponse(const QString& response) {
    this->response = response;
}
