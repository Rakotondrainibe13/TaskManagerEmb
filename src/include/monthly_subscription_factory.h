#ifndef MONTHLY_SUBSCRIPTION_FACTORY_H
#define MONTHLY_SUBSCRIPTION_FACTORY_H

#include "subscription_factory.h"
#include "include/subscription.h"
#include "include/montly_subscription.h"
#include "include/subscription_manager.h"
#include <QDateTime>
#include <memory>

class MonthlySubscriptionFactory : public SubscriptionFactory
{
public:
    MonthlySubscriptionFactory();

    // SubscriptionFactory interface
public:
    virtual SubscriptionPtr createSubscription(int userId, SubscriptionTypePtr subscriptionType, int quantity, QObject *parent) override;
};

#endif // MONTHLY_SUBSCRIPTION_FACTORY_H
