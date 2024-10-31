#ifndef ENCRYPTION_SERVICE_H
#define ENCRYPTION_SERVICE_H

#include <QObject>
#include <QString>
#include <QProcess>

class EncryptionService : public QObject
{
    Q_OBJECT
public:
    explicit EncryptionService(QObject *parent = nullptr);

    QString encryptFile(const QString &filePath);
    void decryptFile(const QString &filePath);
    void generateKeyPair();
    void setM_gpgBinaryPath(const QString& path);
    QString getM_gpgBinaryPath();

private:
    QString m_gpgBinaryPath; // chemin du binaire GPG
    QString m_keyId; // ID de la clé GPG
};


#endif // ENCRYPTION_SERVICE_H
