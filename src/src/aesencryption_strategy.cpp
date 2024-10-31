#include "../include/aesencryption_strategy.h"
#include <QCryptographicHash>

// Implementation AES : encrypt
QByteArray AESEncryptionStrategy::encrypt(const QByteArray& data) {
    QByteArray key = "mySuperSecretKey12345";
    QByteArray result = data;
    for (int i = 0; i < result.size(); ++i) {
        result[i] = result[i] ^ key[i % key.size()];
    }
    return result;
}

// Implementation AES : decrypt
QByteArray AESEncryptionStrategy::decrypt(const QByteArray& encryptedData) {
    QByteArray key = "mySuperSecretKey12345";
    QByteArray result = encryptedData;
    for (int i = 0; i < result.size(); ++i) {
        result[i] = result[i] ^ key[i % key.size()];
    }
    return result;
}

