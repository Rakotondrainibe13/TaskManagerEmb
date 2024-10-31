#include "include/subscription_manager.h"

SubscriptionManager::SubscriptionManager(std::shared_ptr<DatabaseManager> dbManager, QObject *parent): QObject{parent}, m_dbManager(dbManager)
{
}

void SubscriptionManager::initSubscriptionManager()
{
    getAllSubscriptionTypes();

    QSettings setting("TaskEmb","TaskEmb");
    int userId = setting.value("userID").toInt();
    setUserId(userId);

    setSubscriptionList(getAllSubscription());

    SubscriptionPtr currentSub = getCurrentSubscription();

    updateCurrentSubscriptionStatus(currentSub);

}

std::shared_ptr<DatabaseManager> SubscriptionManager::databaseManager() const
{
    return m_dbManager;
}

void SubscriptionManager::setDatabaseManager(const std::shared_ptr<DatabaseManager> &newDatabaseManager)
{
    m_dbManager = newDatabaseManager;
}

QHash<int, SubscriptionTypePtr> SubscriptionManager::subscriptionTypeList() const
{
    return m_subscriptionTypeList;
}

void SubscriptionManager::setSubscriptionTypeList(const QHash<int, SubscriptionTypePtr> &newSubscriptionTypeList)
{
    m_subscriptionTypeList = newSubscriptionTypeList;
}

void SubscriptionManager::getAllSubscriptionTypes()
{
    std::shared_ptr<QSqlDatabase> database = m_dbManager->getDatabase();

    try {
        QSqlQuery query(*database);

        query.prepare("SELECT * FROM SubscriptionTypes");

        if (!query.exec()) {
            qDebug() << "Query execution failed :" << query.lastError().text();
        }


        while (query.next()) {
            SubscriptionTypePtr subscriptionType = std::make_shared<SubscriptionType>();

            subscriptionType->setId(query.value("id").toInt());
            subscriptionType->setSubscriptionName(query.value("subscription_type_name").toString());
            subscriptionType->setPrice(query.value("price").toDouble());
            subscriptionType->setDuration(query.value("duration").toInt());

            m_subscriptionTypeList[subscriptionType->id()] = subscriptionType;
        }

    } catch (const std::exception &e) {
        qWarning() << "An unknown exception occurred on getting all subscription type";
    }
}

void SubscriptionManager::createSubscription(int idSubscriptionType, int quantity)
{

    std::unique_ptr<SubscriptionFactory> subscriptionFactory;

    if (idSubscriptionType == static_cast<int>(SubscriptionTypeIndice::MonthlySubscription)) {
        subscriptionFactory = std::make_unique<MonthlySubscriptionFactory>();
    } else {
        subscriptionFactory = std::make_unique<YearlySubscriptionFactory>();
    }

    QSettings settings("TaskEmb", "TaskEmb");
    int userId = settings.value("userID").toInt();   // id of connected user

    SubscriptionPtr newSubscription = subscriptionFactory->createSubscription(userId, m_subscriptionTypeList[idSubscriptionType], quantity, this);

    m_dbManager->saveSubscription(newSubscription);
    m_subscriptionList.insert(0,newSubscription);

    if (m_currentSubscription == nullptr) updateCurrentSubscriptionStatus(newSubscription);

    emit ui_subscriptionListChanged();
}

SubscriptionPtr SubscriptionManager::getLastSubscription()
{
    QList<SubscriptionPtr> subscriptions;
    SubscriptionMapper subscriptionMapper(subscriptions, m_subscriptionTypeList);

    QString query = QString(R"(
        SELECT * FROM Subscriptions
        where user_id = %1
        ORDER BY subscription_date DESC
        LIMIT 1
    )").arg(m_userId);
    m_dbManager->executeSelectQuery(query, subscriptionMapper);

    return subscriptions.size() > 0 ? subscriptions.first() : nullptr;
}

QList<SubscriptionPtr> SubscriptionManager::getAllSubscription()
{
    QList<SubscriptionPtr> subscriptions;
    SubscriptionMapper subscriptionMapper(subscriptions, m_subscriptionTypeList);

    QString query = QString("SELECT * FROM Subscriptions WHERE user_id = %1 ORDER BY id desc").arg(m_userId);
    m_dbManager->executeSelectQuery(query, subscriptionMapper);

    return subscriptions;

}

SubscriptionPtr SubscriptionManager::getSubscriptionById(int idsubscription)
{
    QList<SubscriptionPtr> subscriptions;
    SubscriptionMapper subscriptionMapper(subscriptions, m_subscriptionTypeList);

    QString query = QString("SELECT * FROM Subscriptions where id = %1").arg(idsubscription);
    m_dbManager->executeSelectQuery(query, subscriptionMapper);

    return subscriptions.first();
}

SubscriptionPtr SubscriptionManager::getCurrentSubscription()
{
    QList<SubscriptionPtr> subscriptions;
    SubscriptionMapper subscriptionMapper(subscriptions, m_subscriptionTypeList);

    QString query = QString(R"(
        SELECT * FROM Subscriptions
        WHERE user_id = %1 AND start_date <= '%2' AND end_date >= '%3'
        ORDER BY end_date DESC
        Limit 1
    )")
    .arg(m_userId)
    .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"))
    .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));

    m_dbManager->executeSelectQuery(query, subscriptionMapper);

    if (subscriptions.size() > 0) {
        setCurrentSubscriptions(subscriptions.first().get());
        return subscriptions.first();
    }else {
        setCurrentSubscriptions(nullptr);
        return nullptr;
    }


}

Subscription *SubscriptionManager::findSubscription(int idSubscription)
{
    for(auto subscription : m_subscriptionList)
        if(subscription->id() == idSubscription) return subscription.get();

    return nullptr;
}

QList<SubscriptionPtr> SubscriptionManager::subscriptionList() const
{
    return m_subscriptionList;
}

void SubscriptionManager::setSubscriptionList(const QList<SubscriptionPtr> &newSubscriptionList)
{
    m_subscriptionList = newSubscriptionList;
}

SubscriptionPtr SubscriptionManager::currentSubscription()
{
    return m_currentSubscription;
}

void SubscriptionManager::setCurrentSubscription(const SubscriptionPtr &newCurrentSubscription)
{
    m_currentSubscription = newCurrentSubscription;
}

QString SubscriptionManager::startDate() const
{
    return m_startDate;
}

void SubscriptionManager::setStartDate(const QString &newStartDate)
{
    if (m_startDate == newStartDate)
        return;
    m_startDate = newStartDate;
    emit startDateChanged();
}

QString SubscriptionManager::endDate() const
{
    return m_endDate;
}

void SubscriptionManager::setEndDate(const QString &newEndDate)
{
    if (m_endDate == newEndDate)
        return;
    m_endDate = newEndDate;
    emit endDateChanged();
}

int SubscriptionManager::userId() const
{
    return m_userId;
}

void SubscriptionManager::setUserId(int newUserId)
{
    m_userId = newUserId;
}

QList<Subscription*> SubscriptionManager::ui_subscriptionList() const
{
    QList<Subscription*> results;
    for (auto subscription : m_subscriptionList) results << subscription.get();
    return results;
}

QString SubscriptionManager::currentSubscriptionType() const
{
    return m_currentSubscriptionType;
}

void SubscriptionManager::setCurrentSubscriptionType(const QString &newCurrentSubscriptionType)
{
    if (m_currentSubscriptionType == newCurrentSubscriptionType)
        return;
    m_currentSubscriptionType = newCurrentSubscriptionType;
    emit currentSubscriptionTypeChanged();
}

QList<SubscriptionType*> SubscriptionManager::getSubscriptionTypeList() {
    QList<SubscriptionType*> results;
    for (auto it =m_subscriptionTypeList.begin(); it != m_subscriptionTypeList.end(); ++it) {
        results.append(it.value().get());
    }
    return results;
}

void SubscriptionManager::updateCurrentSubscriptionStatus(SubscriptionPtr currentSub)
{
    if (currentSub) {
        setCurrentSubscription(getCurrentSubscription());
        setStartDate(currentSub->startDate().toString("dddd d MMMM yyyy"));
        setEndDate(currentSub->endDate().toString("dddd d MMMM yyyy"));
        setCurrentSubscriptionType(currentSub->subscriptionType()->subscriptionName());
    } else {
        setStartDate("-");
        setEndDate("-");
        setCurrentSubscriptionType("Vous n'êtes pas abonnez !");
    }
}

Subscription* SubscriptionManager::getCurrentSubscriptions() const {
    return m_currentSubscriptions;
}

void SubscriptionManager::setCurrentSubscriptions(Subscription* currentSubscription) {
    if (m_currentSubscriptions != currentSubscription) {
        m_currentSubscriptions = currentSubscription;
        emit currentSubscriptionChangeds();
    }
}
