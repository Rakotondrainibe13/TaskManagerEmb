#ifndef YEARLY_SUBSCRIPTION_H
#define YEARLY_SUBSCRIPTION_H

#include "subscription.h"


class YearlySubscription : public Subscription
{
public:
    YearlySubscription(const int &userId, const SubscriptionTypePtr &subscriptionType, const int &quantity, const QDateTime &startDate, const QDateTime &endDate, const double &price, const int &duration, const QDateTime &subscriptionDate, QObject *parent);
};

#endif // YEARLY_SUBSCRIPTION_H
