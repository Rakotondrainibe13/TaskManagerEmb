#ifndef ENCRYPTION_STRATEGY_H
#define ENCRYPTION_STRATEGY_H

#include <QByteArray>

class EncryptionStrategy{
    public:
        virtual ~EncryptionStrategy() = default;
        virtual QByteArray encrypt(const QByteArray& data) = 0;
        virtual QByteArray decrypt(const QByteArray& encryptData) = 0;
};

#endif