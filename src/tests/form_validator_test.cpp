#include "form_validator_test.h"

void FormValidatorTest::testValidateEmail() {
    QVERIFY(!FormValidator::validateEmail("invalid-email"));
    QVERIFY(!FormValidator::validateEmail("test@.com"));
    QVERIFY(!FormValidator::validateEmail("test@com"));
}

void FormValidatorTest::testValidatePassword() {
    QVERIFY(FormValidator::validatePassword("password123"));
    QVERIFY(!FormValidator::validatePassword("short"));
    QVERIFY(FormValidator::validatePassword("longenoughpassword"));
}

void FormValidatorTest::testValidateTaskTitle() {
    QVERIFY(FormValidator::validateTaskTitle("Valid Task Title"));
    QVERIFY(!FormValidator::validateTaskTitle(""));
    QString longTitle(101, 'a'); // 101 characters long
    QVERIFY(!FormValidator::validateTaskTitle(longTitle));
    QString validTitle(100, 'a'); // 100 characters long
    QVERIFY(FormValidator::validateTaskTitle(validTitle));
}

void FormValidatorTest::testValidateTaskDescription() {
    QVERIFY(FormValidator::validateTaskDescription("This is a valid task description."));
    QString longDescription(501, 'a'); // 501 characters long
    QVERIFY(!FormValidator::validateTaskDescription(longDescription));
    QString validDescription(500, 'a'); // 500 characters long
    QVERIFY(FormValidator::validateTaskDescription(validDescription));
}

void FormValidatorTest::testValidateTaskDueDate() {
    QVERIFY(FormValidator::validateTaskDueDate(QDateTime::currentDateTime().addDays(1))); // Future date
    QVERIFY(!FormValidator::validateTaskDueDate(QDateTime::currentDateTime().addDays(-1))); // Past date
}

//QTEST_MAIN(FormValidatorTest)
