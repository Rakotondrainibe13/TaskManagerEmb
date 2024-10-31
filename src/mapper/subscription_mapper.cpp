#include "include/subscription_mapper.h"

SubscriptionMapper::SubscriptionMapper(QList<SubscriptionPtr> &results, QHash<int, SubscriptionTypePtr> &subscriptionTypeList): m_results(results), m_subscriptionTypeList(subscriptionTypeList) {}

void SubscriptionMapper::map(QSqlQuery &query)
{
    SubscriptionPtr subscription = std::make_shared<Subscription>();

    subscription->setId(query.value("id").toInt());
    subscription->setUserId(query.value("user_id").toInt());
    subscription->setQuantity(query.value("quantity").toInt());
    subscription->setStartDate(query.value("start_date").toDateTime());
    subscription->setEndDate(query.value("end_date").toDateTime());
    subscription->setPrice(query.value("price").toDouble());
    subscription->setDuration(query.value("duration").toInt());
    subscription->setSubscriptionDate(query.value("subscription_date").toDateTime());
    subscription->setStatus(query.value("status").toInt());
    SubscriptionTypePtr type = m_subscriptionTypeList[query.value("subscription_type_id").toInt()];
    subscription->setSubscriptionType(type);

    m_results << subscription;
}
