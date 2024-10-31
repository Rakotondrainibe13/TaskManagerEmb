#ifndef SUBSCRIPTION_FACTORY_H
#define SUBSCRIPTION_FACTORY_H

#include "subscription.h"
#include <QDebug>
class SubscriptionFactory
{
public:
    SubscriptionFactory();

    virtual SubscriptionPtr createSubscription(int userId, SubscriptionTypePtr subscriptionType, int quantity, QObject* parent) = 0;
};

#endif // SUBSCRIPTION_FACTORY_H
