#ifndef SUBSCRIPTION_MAPPER_H
#define SUBSCRIPTION_MAPPER_H

#include "imodel_mapper.h"
#include <memory>
#include "subscription.h"

class SubscriptionMapper : public IModelMapper
{
public:
    SubscriptionMapper(QList<SubscriptionPtr> &results, QHash<int, SubscriptionTypePtr> &subscriptionTypeList);
    void map(QSqlQuery &query) override;
private:
    QList<SubscriptionPtr>& m_results;
    QHash<int, SubscriptionTypePtr>& m_subscriptionTypeList;

};

#endif // SUBSCRIPTION_MAPPER_H
