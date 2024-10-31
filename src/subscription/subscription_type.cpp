#include "../include/subscription_type.h"

SubscriptionType::SubscriptionType(QObject *parent): QObject{parent}
{

}

int SubscriptionType::id() const
{
    return m_id;
}

void SubscriptionType::setId(int newId)
{
    if (m_id == newId)
        return;
    m_id = newId;
    emit idChanged();
}

QString SubscriptionType::subscriptionName() const
{
    return m_subscriptionName;
}

void SubscriptionType::setSubscriptionName(const QString &newSubscriptionName)
{
    if (m_subscriptionName == newSubscriptionName)
        return;
    m_subscriptionName = newSubscriptionName;
    emit subscriptionNameChanged();
}

double SubscriptionType::price() const
{
    return m_price;
}

void SubscriptionType::setPrice(double newPrice)
{
    if (qFuzzyCompare(m_price, newPrice))
        return;
    m_price = newPrice;
    emit priceChanged();
}

int SubscriptionType::duration() const
{
    return m_duration;
}

void SubscriptionType::setDuration(int newDuration)
{
    if (m_duration == newDuration)
        return;
    m_duration = newDuration;
    emit durationChanged();
}
