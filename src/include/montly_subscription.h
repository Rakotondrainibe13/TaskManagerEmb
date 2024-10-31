#ifndef MONTLY_SUBSCRIPTION_H
#define MONTLY_SUBSCRIPTION_H

#include <QDateTime>
#include "subscription.h"


class MontlySubscription : public Subscription
{
public:
    MontlySubscription(const int &userId, const SubscriptionTypePtr &subscriptionType, const int &quantity, const QDateTime &startDate, const QDateTime &endDate, const double &price, const int &duration, const QDateTime &subscriptionDate, QObject *parent);
};

#endif // MONTLY_SUBSCRIPTION_H
