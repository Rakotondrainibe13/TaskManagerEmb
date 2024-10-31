#include "include/montly_subscription.h"

MontlySubscription::MontlySubscription(const int &userId, const SubscriptionTypePtr &subscriptionType, const int &quantity, const QDateTime &startDate, const QDateTime &endDate, const double &price, const int &duration, const QDateTime &subscriptionDate, QObject *parent):Subscription{userId, subscriptionType, quantity, startDate, endDate, price, duration, subscriptionDate, parent} {}
