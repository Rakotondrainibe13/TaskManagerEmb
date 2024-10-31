#include "include/yearly_subscription_factory.h"

YearlySubscriptionFactory::YearlySubscriptionFactory() {}

SubscriptionPtr YearlySubscriptionFactory::createSubscription(int userId, SubscriptionTypePtr subscriptionType, int quantity, QObject *parent)
{
    SubscriptionManager* subscriptionManager = dynamic_cast<SubscriptionManager*>(parent);
    SubscriptionPtr lastSubscription = subscriptionManager->getLastSubscription();

    QDateTime startDate;
    if (lastSubscription == nullptr || lastSubscription->endDate() < QDateTime::currentDateTime())
    {
        startDate = QDateTime::currentDateTime();
    }
    else
    {
        startDate = lastSubscription->endDate();
    }

    QDateTime endDate = startDate.addDays(subscriptionType->duration() * quantity);

    std::shared_ptr<YearlySubscription> yearlySubscription = std::make_shared<YearlySubscription>(userId, subscriptionType, quantity, startDate, endDate, subscriptionType->price() * quantity, subscriptionType->duration(), QDateTime::currentDateTime(), parent);

    return yearlySubscription;
}
