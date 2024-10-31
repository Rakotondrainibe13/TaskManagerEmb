#include "../../../src/include/security_manager.h"
#include "../../../src/include/database_manager.h"
#include "../../../src/include/encryption_strategy.h"
#include <QByteArray>
#include <QString>
#include <memory>

class MockEncryptionStrategy : public EncryptionStrategy {
public:
    QByteArray encrypt(const QByteArray& data) override {
        return "encrypted_" + data;
    }

    QByteArray decrypt(const QByteArray& data) override {
        return data.mid(10);
    }
};

TEST(SecurityManagerTest, EncryptDecryptData) {
    SecurityManager manager;
    manager.setEncryptionStrategy(std::make_unique<MockEncryptionStrategy>());

    QByteArray data = "Sensitive Data";
    QByteArray encryptedData = manager.encryptData(data);
    QByteArray decryptedData = manager.decryptData(encryptedData);

    EXPECT_EQ(encryptedData, "encrypted_Sensitive Data");
    EXPECT_EQ(decryptedData, data);
}


TEST(SecurityManagerTest, SuccessfulAuthentication) {
    SecurityManager manager;
    bool authenticated = manager.authenticate("validUser", "validPassword");
    EXPECT_TRUE(authenticated);
    EXPECT_TRUE(manager.isLoggedIn());
}

TEST(SecurityManagerTest, LogSecurityEvent) {
    SecurityManager manager;
    QObject::connect(&manager, &SecurityManager::securityEvent, [](const QString& event){
        EXPECT_EQ(event, "Test Event");
    });
    manager.logSecurityEvent("Test Event");
}

TEST(SecurityManagerTest, ChangeEncryptionStrategy) {
    SecurityManager manager;
    manager.setEncryptionStrategy(std::make_unique<MockEncryptionStrategy>());
    QByteArray data = "Sensitive Data";
    QByteArray encryptedData = manager.encryptData(data);
    EXPECT_EQ(encryptedData, "encrypted_Sensitive Data");

    class AnotherMockEncryptionStrategy : public EncryptionStrategy {
    public:
        QByteArray encrypt(const QByteArray& data) override {
            return "another_encrypted_" + data;
        }

        QByteArray decrypt(const QByteArray& data) override {
            return data.mid(17);
        }
    };

    manager.setEncryptionStrategy(std::make_unique<AnotherMockEncryptionStrategy>());
    encryptedData = manager.encryptData(data);
    EXPECT_EQ(encryptedData, "another_encrypted_Sensitive Data");
}
