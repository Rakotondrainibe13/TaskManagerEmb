#ifndef FORM_VALIDATOR_TEST_H
#define FORM_VALIDATOR_TEST_H


#pragma once
#include <QObject>
#include <QtTest>

#include "../include/form_validator.h"

class FormValidatorTest : public QObject {
    Q_OBJECT

private slots:
    void testValidateEmail();
    void testValidatePassword();
    void testValidateTaskTitle();
    void testValidateTaskDescription();
    void testValidateTaskDueDate();
};

#endif // FORM_VALIDATOR_TEST_H
