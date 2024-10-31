#pragma once
#include <QString>
#include <QRegularExpression>
#include <QObject>
class FormValidator: public QObject {
    Q_OBJECT
public:
    explicit FormValidator(QObject* parent = nullptr) : QObject(parent) {}
    Q_INVOKABLE static bool validateEmail(const QString& email);
    Q_INVOKABLE static bool validatePassword(const QString& password);
    Q_INVOKABLE static bool validateTaskTitle(const QString& title);
    Q_INVOKABLE static bool validateTaskDescription(const QString& description);
    Q_INVOKABLE static bool validateTaskDueDate(const QDateTime& dueDate);
    void validateTaskFormWithError(const QString& email, const QString& password, const QString& title, const QString& description, const QDateTime& dueDate);
    QString validateTaskForm(const QString& email, const QString& password, const QString& title, const QString& description, const QDateTime& dueDate);

    bool validateTitleForm(const QString& title);
    bool validateDescriptionForm(const QString& description);
    bool validateDueDateForm(const QDateTime& dueDate);


    bool validateEmailFormText(const QString& email);
    bool validatePasswordFormText(const QString& password);

    Q_INVOKABLE bool validateTaskCreate(const QString& title, const QString& description, const QDateTime& dueDate);

private:
    static const QRegularExpression EMAIL_REGEX;
    static const int MIN_PASSWORD_LENGTH;
    static const int MAX_TITLE_LENGTH;
    static const int MAX_DESCRIPTION_LENGTH;

signals:
    void validationTaskFormFailed(const QString& errorMessage);
    void validateEmailFailed(const QString& errorMessage);
    void validateTitleFailed(const QString& errorMessage);
    void validateDescriptionFailed(const QString& errorMessage);
    void validateDueDateFailed(const QString& errorMessage);
    void validatePasswordFailed(const QString& password);
};
