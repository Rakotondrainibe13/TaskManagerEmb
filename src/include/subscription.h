#ifndef SUBSCRIPTION_H
#define SUBSCRIPTION_H

#include <QDateTime>
#include <QObject>
#include <memory>

#include "subscription_type.h"

class Subscription;
using SubscriptionPtr = std::shared_ptr<Subscription>;
class Subscription : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged FINAL)
    Q_PROPERTY(int userId READ userId WRITE setUserId NOTIFY userIdChanged FINAL)
    Q_PROPERTY(SubscriptionType* subscriptionType READ getSubscriptionType NOTIFY subscriptionTypeChanged)
    Q_PROPERTY(int quantity READ quantity WRITE setQuantity NOTIFY quantityChanged FINAL)
    Q_PROPERTY(QDateTime startDate READ startDate WRITE setStartDate NOTIFY startDateChanged FINAL)
    Q_PROPERTY(QDateTime endDate READ endDate WRITE setEndDate NOTIFY endDateChanged FINAL)
    Q_PROPERTY(double price READ price WRITE setPrice NOTIFY priceChanged FINAL)
    Q_PROPERTY(int duration READ duration WRITE setDuration NOTIFY durationChanged FINAL)
    Q_PROPERTY(QDateTime subscriptionDate READ subscriptionDate WRITE setSubscriptionDate NOTIFY subscriptionDateChanged FINAL)
    Q_PROPERTY(QString status READ subscriptionStatus NOTIFY subscriptionStatusChanged)

public:
    explicit Subscription(QObject *parent = nullptr);
    Subscription(const int &userId, const SubscriptionTypePtr &subscriptionType, const int &quantity, const QDateTime &startDate, const QDateTime &endDate, const double &price, const int &duration, const QDateTime &subscriptionDate, QObject *parent);

    int id() const;
    void setId(int newId);

    int userId() const;
    void setUserId(int newUserId);

    SubscriptionType* getSubscriptionType() const;
    SubscriptionTypePtr subscriptionType() const;
    void setSubscriptionType(SubscriptionTypePtr newSubscriptionType);

    int quantity() const;
    void setQuantity(int newQuantity);

    QDateTime startDate() const;
    void setStartDate(const QDateTime &newStartDate);

    QDateTime endDate() const;
    void setEndDate(const QDateTime &newEndDate);

    double price() const;
    void setPrice(double newPrice);

    int duration() const;
    void setDuration(int newDuration);

    QDateTime subscriptionDate() const;
    void setSubscriptionDate(const QDateTime &newSubscriptionDate);

    int status() const;
    void setStatus(int newStatus);
    QString subscriptionStatus() const;

signals:
    void idChanged();

    void userIdChanged();

    void subscriptionTypeChanged();

    void quantityChanged();

    void startDateChanged();

    void endDateChanged();

    void priceChanged();

    void durationChanged();

    void subscriptionDateChanged();

    void statusChanged();

    void subscriptionStatusChanged();

private:
    int m_id;
    int m_userId;
    SubscriptionTypePtr m_subscriptionType;
    int m_quantity;
    QDateTime m_startDate;
    QDateTime m_endDate;
    double m_price;
    int m_duration;
    QDateTime m_subscriptionDate;
    int m_status;
};

#endif // SUBSCRIPTION_H
