#include "../include/form_validator.h"
#include <QDateTime>

const QRegularExpression FormValidator::EMAIL_REGEX("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
const int FormValidator::MIN_PASSWORD_LENGTH = 8;
const int FormValidator::MAX_TITLE_LENGTH = 255;
const int FormValidator::MAX_DESCRIPTION_LENGTH = 500;

bool FormValidator::validateEmail(const QString& email) {
    qDebug() << "LAUkkk ===" << EMAIL_REGEX.match(email).hasMatch();
    return EMAIL_REGEX.match(email).hasMatch();
}

bool FormValidator::validatePassword(const QString& password) {
    return password.length() >= MIN_PASSWORD_LENGTH;
}

bool FormValidator::validateTaskTitle(const QString& title) {
    // qDebug() << "processing validateTaskTitle ....";
    return !title.isEmpty() && title.length() <= MAX_TITLE_LENGTH;
}

bool FormValidator::validateTaskDescription(const QString& description) {
    return description.length() <= MAX_DESCRIPTION_LENGTH;
}

bool FormValidator::validateTaskDueDate(const QDateTime& dueDate) {
    qDebug() << "Due Date : " << dueDate << "resultat : " <<  (dueDate > QDateTime::currentDateTime());
    return dueDate > QDateTime::currentDateTime();
}


QString FormValidator::validateTaskForm(const QString& email, const QString& password, const QString& title, const QString& description, const QDateTime& dueDate) {
    if (!this->validateEmail(email)) {
        return "Invalid email address.";
    }
    if (!this->validatePassword(password)) {
        return "Password is too weak.";
    }
    if (!this->validateTaskTitle(title)) {
        return "Title is too long.";
    }
    if (!this->validateTaskDescription(description)) {
        return "Description is too long.";
    }
    if (!this->validateTaskDueDate(dueDate)) {
        return "Due date is invalid.";
    }
    return "";
}
void FormValidator::validateTaskFormWithError(const QString& email, const QString& password, const QString& title, const QString& description, const QDateTime& dueDate) {
    // QString error = validateTaskForm(email, password, title, description, dueDate);
    validateEmail(email);
    validateTitleForm(title);
    validateDescriptionForm(description);
    validateDueDateForm(dueDate);
}

bool FormValidator::validateTaskCreate(const QString& title, const QString& description, const QDateTime& dueDate){
    // bool ret = false;
    // ret = this->validateTitleForm(title);
    // ret = this->validateDescriptionForm(description);
    // ret = this->validateDueDateForm(dueDate);
    if (this->validateTitleForm(title) && this->validateDescriptionForm(description) && this->validateDueDateForm(dueDate))
    {
        return true;
    }
    return false;
}

bool FormValidator::validateTitleForm(const QString& title){
    if (!this->validateTaskTitle(title)) {
        QString error = "Title is blank or too long.";
        emit validateTitleFailed(error);
        return false;
    }
    return true;
}

bool FormValidator::validateDescriptionForm(const QString& description){
    if (!this->validateTaskDescription(description)) {
        QString error = "Description is too long.";
        emit validateDescriptionFailed(error);
        return false;
    }
    return true;
}

bool FormValidator::validateDueDateForm(const QDateTime& dueDate){
    if (!this->validateTaskDueDate(dueDate)) {
        QString error = "Due date is invalid.";
        emit validateDueDateFailed(error);
        return false;
    }
    return true;
}

bool FormValidator::validateEmailFormText(const QString& email) {
    if (!this->validateEmail(email)) {
        QString error =  "Invalid email address.";
        emit validateEmailFailed(error);
        return false;
    }
    return true;
}

bool FormValidator::validatePasswordFormText(const QString& password) {
    if (!this->validatePassword(password)) {
        QString error =  "Password is too weak.";
        emit validatePasswordFailed(error);
        return false;
    }
    return true;
}
