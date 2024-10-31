#include "../include/synch_config.h"
#include <QDebug>
#include <iostream>
#include <QFile>
#include <QTextStream>

SynchConfig::SynchConfig(QObject* parent) : QObject(parent) {
};
SynchConfig::~SynchConfig(){};

QString SynchConfig::parseValue(const QString& line, const QString& key) {
    if (line.startsWith(key)) {
        return line.split("=").last().trimmed();
    }
    return "";
}
void SynchConfig::saveConfig(const QString &filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Could not open config.ini file!";
        return;
    }
    QTextStream in(&file);
    QString currentSection;
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        // Ignore empty lines or comments
        if (line.isEmpty() || line.startsWith('#') || line.startsWith(';')) {
            continue;
        }
        // Check if it's a section header
        if (line.startsWith("[") && line.endsWith("]")) {
            currentSection = line.mid(1, line.length() - 2).trimmed();
            continue;
        }
        // Only process the "Synch" section
        if (currentSection == "Synch") {
            if (backUpDirectory.isEmpty()) { backUpDirectory = parseValue(line, "backUpDirectory"); }
            if (gpgBinaryPath.isEmpty()) { gpgBinaryPath = parseValue(line, "gpgBinaryPath"); }
            if (remoteServer.isEmpty()) { remoteServer = parseValue(line, "remoteServer"); }
            if (ipServerCentral.isEmpty()) { ipServerCentral = parseValue(line, "ipServerCentral"); }
            if (port.isEmpty()) { port = parseValue(line, "port"); }
            if (username.isEmpty()) { username = parseValue(line, "username"); }
            if (password.isEmpty()) { password = parseValue(line, "password"); }
        }
    }
}
