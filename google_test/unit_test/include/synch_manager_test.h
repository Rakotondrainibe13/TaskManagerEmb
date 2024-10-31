#pragma once
#include "../../../src/include/encryption_service.h"
#include "../../../src/include/ssh_manager.h"
#include "../../../src/include/exception_manager.h"
#include "../../../src/include/synch_manager.h"
#include <QString>
#include <QDateTime>

TEST(SynchManagerTest, EncrypteFile)
{
    EncryptionService encrypte(nullptr);
    encrypte.setM_gpgBinaryPath("/usr/bin/gpg");
    encrypte.generateKeyPair();
    QString encrypte_file_name_test = encrypte.encryptFile("../../../build/Desktop_Qt_6_7_2-Debug/src/database.dump");
    QString currentDateTimeString = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    currentDateTimeString.replace(" ", "_");
    QString encrypte_file_name = currentDateTimeString + ".dump.gpg";
    EXPECT_TRUE(encrypte_file_name_test == encrypte_file_name);
}

TEST(SynchManagerTest, ExecuteCommande)
{
    SSHManager ssh;
    try
    {
        ssh.executeCommand(" huhu ");
        FAIL() << "TEST FAIL";
    }
    catch (const ExceptionManager &e)
    {
        EXPECT_EQ(e.message(), QString("SSH Error"));
    }
}

TEST(SynchManagerTest, RetentionConfig)
{
    try
    {
        std::shared_ptr<SynchManager> synch;
        synch = SynchManager::getInstance(nullptr);
        int mois(0), jour(0), heure(0), minute(0);
        synch->retentionBackup(mois, jour, heure, minute);
        FAIL() << "TEST FAIL";
    }
    catch (const ExceptionManager &e)
    {
        EXPECT_EQ(e.message(), QString("All parameters (month, day, hour, minute) are set to 0. Retention has not been configured."));
    }
}
