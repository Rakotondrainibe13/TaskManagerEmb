#include "../include/subscription.h"

Subscription::Subscription(QObject *parent) : QObject{parent}
{

}

Subscription::Subscription(const int &userId, const SubscriptionTypePtr &subscriptionType, const int &quantity, const QDateTime &startDate, const QDateTime &endDate, const double &price, const int &duration, const QDateTime &subscriptionDate, QObject *parent)
    : QObject{parent}, m_userId(userId), m_subscriptionType(subscriptionType), m_quantity(quantity), m_startDate(startDate), m_endDate(endDate), m_price(price), m_duration(duration), m_subscriptionDate(subscriptionDate)
{

}

int Subscription::id() const
{
    return m_id;
}

void Subscription::setId(int newId)
{
    if (m_id == newId)
        return;
    m_id = newId;
    emit idChanged();
}

int Subscription::userId() const
{
    return m_userId;
}

void Subscription::setUserId(int newUserId)
{
    if (m_userId == newUserId)
        return;
    m_userId = newUserId;
    emit userIdChanged();
}

SubscriptionType* Subscription::getSubscriptionType() const
{
    return m_subscriptionType.get();
}

SubscriptionTypePtr Subscription::subscriptionType() const
{
    return m_subscriptionType;
}

void Subscription::setSubscriptionType(SubscriptionTypePtr newSubscriptionType)
{
    if (m_subscriptionType == newSubscriptionType)
        return;
    m_subscriptionType = newSubscriptionType;
}

int Subscription::quantity() const
{
    return m_quantity;
}

void Subscription::setQuantity(int newQuantity)
{
    if (m_quantity == newQuantity)
        return;
    m_quantity = newQuantity;
    emit quantityChanged();
}

QDateTime Subscription::startDate() const
{
    return m_startDate;
}

void Subscription::setStartDate(const QDateTime &newStartDate)
{
    if (m_startDate == newStartDate)
        return;
    m_startDate = newStartDate;
    emit startDateChanged();
}

QDateTime Subscription::endDate() const
{
    return m_endDate;
}

void Subscription::setEndDate(const QDateTime &newEndDate)
{
    if (m_endDate == newEndDate)
        return;
    m_endDate = newEndDate;
    emit endDateChanged();
}

double Subscription::price() const
{
    return m_price;
}

void Subscription::setPrice(double newPrice)
{
    if (qFuzzyCompare(m_price, newPrice))
        return;
    m_price = newPrice;
    emit priceChanged();
}

int Subscription::duration() const
{
    return m_duration;
}

void Subscription::setDuration(int newDuration)
{
    if (m_duration == newDuration)
        return;
    m_duration = newDuration;
    emit durationChanged();
}

QDateTime Subscription::subscriptionDate() const
{
    return m_subscriptionDate;
}

void Subscription::setSubscriptionDate(const QDateTime &newSubscriptionDate)
{
    if (m_subscriptionDate == newSubscriptionDate)
        return;
    m_subscriptionDate = newSubscriptionDate;
    emit subscriptionDateChanged();
}

int Subscription::status() const
{
    return m_status;
}

void Subscription::setStatus(int newStatus)
{
    if (m_status == newStatus)
        return;
    m_status = newStatus;
    emit statusChanged();
}

QString Subscription::subscriptionStatus() const
{
    if (m_endDate < QDateTime::currentDateTime()) {
        return "Completed";
    }
    else if (m_startDate <= QDateTime::currentDateTime() && QDateTime::currentDateTime() <= m_endDate)
    {
        return "Active";
    }
    else
    {
        return "Upcoming";
    }
}
