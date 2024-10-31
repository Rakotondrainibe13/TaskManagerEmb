#include <QDebug>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QStandardPaths>
#include <iostream>
#include "../include/encryption_service.h"
#include "../include/ssh_manager.h"

EncryptionService::EncryptionService(QObject *parent) : QObject(parent) {
    // Implémentation
}

QString EncryptionService::encryptFile(const QString &filePath){
    // Crée un processus GPG pour chiffrer le fichier
    QString currentDateTimeString = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    currentDateTimeString.replace(" ", "_");
    QString encrypte_file_name = currentDateTimeString+".dump.gpg";
    QProcess gpgProcess;
    gpgProcess.setProgram(m_gpgBinaryPath);
    gpgProcess.setArguments({"--encrypt", "--recipient", m_keyId, "--output", encrypte_file_name, filePath});
    gpgProcess.start();
    gpgProcess.waitForFinished();
    // Vérifie si le chiffrement a réussi
    if (gpgProcess.exitCode() == 0) {
        qDebug() << "SUCCESS encryption";
    } else {
        qDebug() << "ERROR encryption";
    }
    return encrypte_file_name;
}

void EncryptionService::decryptFile(const QString &filePath){
    // Crée un processus GPG pour déchiffrer le fichier
    QProcess gpgProcess;
    gpgProcess.setProgram(m_gpgBinaryPath);
    gpgProcess.setArguments({"--decrypt", filePath});
    gpgProcess.start();
    gpgProcess.waitForFinished();
    // Vérifie si le déchiffrement a réussi
    if (gpgProcess.exitCode() == 0) {
        qDebug() << "File decrypted successfully";
    } else {
        qDebug() << "Error decrypting file";
    }
}

void EncryptionService::generateKeyPair(){
    // check if file.rev already exist
    QString homeDir = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
    QString gnupgDir = ".gnupg";
    QDir dir(homeDir + "/" + gnupgDir);
    dir.cd("openpgp-revocs.d");
    QStringList files = dir.entryList(QStringList() << "*.rev");
    if (files.isEmpty())
    {
        // generate the file.rev in /home/user_name/.gnupg/openpgp-revocs.d/...
        QProcess process;
        process.start("bash", QStringList() << "-c" << "gpg --batch --gen-key --yes --passphrase '' --default-new-key-algo rsa2048 << EOF\n%no-protection\nKey-Type: RSA\nKey-Length: 2048\nSubkey-Type: ELG-E\nSubkey-Length: 2048\nName-Real: Central\nName-Email: central@gmail.com\nExpire-Date: 0\nEOF");
        process.waitForFinished();
        files = dir.entryList(QStringList() << "*.rev");
    }
    // set the keyId
    files[0].replace(".rev", "");
    m_keyId = files[0];
}

void EncryptionService::setM_gpgBinaryPath(const QString& path)
{
    m_gpgBinaryPath = path;
}

QString EncryptionService::getM_gpgBinaryPath()
{
    return m_gpgBinaryPath;
}
