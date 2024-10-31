#ifndef SUBSCRIPTION_MANAGER_H
#define SUBSCRIPTION_MANAGER_H

#include <QObject>
#include <QDebug>
#include <QSqlQuery>
#include <QSettings>
#include <memory>
#include "include/subscription_type.h"
#include "include/subscription_factory.h"
#include "include/monthly_subscription_factory.h"
#include "include/yearly_subscription_factory.h"
#include "include/database_manager.h"
#include "include/subscription_mapper.h"


class SubscriptionManager : public QObject {
    Q_OBJECT
    Q_PROPERTY(QList<SubscriptionType*> ui_subscriptionType READ getSubscriptionTypeList FINAL)
    Q_PROPERTY(QList<Subscription*> ui_subscriptionList READ ui_subscriptionList NOTIFY ui_subscriptionListChanged FINAL)
    Q_PROPERTY(QString startDate READ startDate WRITE setStartDate NOTIFY startDateChanged FINAL)
    Q_PROPERTY(QString endDate READ endDate WRITE setEndDate NOTIFY endDateChanged FINAL)
    Q_PROPERTY(QString currentSubscriptionType READ currentSubscriptionType WRITE setCurrentSubscriptionType NOTIFY currentSubscriptionTypeChanged FINAL)
    Q_PROPERTY(Subscription* currentSubscriptions READ getCurrentSubscriptions WRITE setCurrentSubscriptions NOTIFY currentSubscriptionChangeds FINAL)


public:
    enum class SubscriptionTypeIndice {
        MonthlySubscription = 1,
        YearlySubscription = 2
    };

    explicit SubscriptionManager(std::shared_ptr<DatabaseManager> databaseManager, QObject *parent = nullptr);
    void initSubscriptionManager();

    std::shared_ptr<DatabaseManager> databaseManager() const;
    void setDatabaseManager(const std::shared_ptr<DatabaseManager> &newDatabaseManager);

    QHash<int, SubscriptionTypePtr> subscriptionTypeList() const;
    void setSubscriptionTypeList(const QHash<int, SubscriptionTypePtr> &newSubscriptionTypeList);

    void getAllSubscriptionTypes();

    Q_INVOKABLE void createSubscription(int idSubscriptionType, int quantity);

    SubscriptionPtr getLastSubscription();
    QList<SubscriptionPtr> getAllSubscription();
    SubscriptionPtr getSubscriptionById(int idsubscription);
    SubscriptionPtr getCurrentSubscription();


    QList<SubscriptionPtr> subscriptionList() const;
    void setSubscriptionList(const QList<SubscriptionPtr> &newSubscriptionList);

    void setCurrentSubscription(const SubscriptionPtr &newCurrentSubscription);
    SubscriptionPtr currentSubscription();


    QString startDate() const;
    void setStartDate(const QString &newStartDate);

    QString endDate() const;
    void setEndDate(const QString &newEndDate);

    int userId() const;
    void setUserId(int newUserId);

    QList<Subscription *> ui_subscriptionList() const;
    void setUi_subscriptionList(const QList<Subscription *> &newUi_subscriptionList);

    QString currentSubscriptionType() const;
    void setCurrentSubscriptionType(const QString &newCurrentSubscriptionType);

    QList<SubscriptionType*> getSubscriptionTypeList();
    Subscription* getCurrentSubscriptions() const;
    void setCurrentSubscriptions(Subscription* currentSubscription);

    void updateCurrentSubscriptionStatus(SubscriptionPtr currentSubscription);

signals:
    void startDateChanged();

    void endDateChanged();

    void ui_subscriptionListChanged();

    void currentSubscriptionTypeChanged();

    void currentSubscriptionChangeds();


public slots:
    Subscription* findSubscription(int idSubcription);

private:
    QHash<int, SubscriptionTypePtr> m_subscriptionTypeList;
    std::shared_ptr<DatabaseManager> m_dbManager;
    QList<SubscriptionPtr> m_subscriptionList;
    SubscriptionPtr m_currentSubscription;
    int m_userId;
    QString m_startDate;
    QString m_endDate;
    QString m_currentSubscriptionType;
    Subscription* m_currentSubscriptions;
};

#endif // SUBSCRIPTION_MANAGER_H
