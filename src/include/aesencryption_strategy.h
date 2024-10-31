#ifndef AESENCRYPTION_STRATEGY_H
#define AESENCRYPTION_STRATEGY_H

#include "../include/encryption_strategy.h"

class AESEncryptionStrategy : public EncryptionStrategy {
    public :
        QByteArray encrypt(const QByteArray& data) override;
        QByteArray decrypt(const QByteArray& encryptData) override;
};

#endif