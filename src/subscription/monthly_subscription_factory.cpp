#include "include/monthly_subscription_factory.h"

MonthlySubscriptionFactory::MonthlySubscriptionFactory() {}

SubscriptionPtr MonthlySubscriptionFactory::createSubscription(int userId, SubscriptionTypePtr subscriptionType, int quantity, QObject *parent)
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

    std::shared_ptr<MontlySubscription> monthlySubscription = std::make_shared<MontlySubscription>(userId, subscriptionType, quantity, startDate, endDate, subscriptionType->price() * quantity, subscriptionType->duration(), QDateTime::currentDateTime(), parent);

    return monthlySubscription;
}
