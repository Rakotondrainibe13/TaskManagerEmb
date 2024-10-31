#ifndef YEARLY_SUBSCRIPTION_FACTORY_H
#define YEARLY_SUBSCRIPTION_FACTORY_H

#include "subscription_factory.h"
#include "yearly_subscription_factory.h"
#include "yearly_subscription.h"
#include "subscription.h"
#include "subscription_manager.h"
#include <memory>

class YearlySubscriptionFactory : public SubscriptionFactory
{
public:
    YearlySubscriptionFactory();

    // SubscriptionFactory interface
public:
    virtual SubscriptionPtr createSubscription(int userId, SubscriptionTypePtr subscriptionType, int quantity, QObject *parent) override;
};

#endif // YEARLY_SUBSCRIPTION_FACTORY_H
