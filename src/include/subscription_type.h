#ifndef SUBSCRIPTION_TYPE_H
#define SUBSCRIPTION_TYPE_H

#include <QObject>
#include <memory>

class SubscriptionType;
using SubscriptionTypePtr = std::shared_ptr<SubscriptionType>;
class SubscriptionType : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged FINAL)
    Q_PROPERTY(QString subscriptionName READ subscriptionName WRITE setSubscriptionName NOTIFY subscriptionNameChanged FINAL)
    Q_PROPERTY(double price READ price WRITE setPrice NOTIFY priceChanged FINAL)
    Q_PROPERTY(int duration READ duration WRITE setDuration NOTIFY durationChanged FINAL)

public:
    explicit SubscriptionType(QObject *parent = nullptr);

    int id() const;
    void setId(int newId);

    QString subscriptionName() const;
    void setSubscriptionName(const QString &newSubscriptionName);

    double price() const;
    void setPrice(double newPrice);

    int duration() const;
    void setDuration(int newDuration);

signals:
    void idChanged();

    void subscriptionNameChanged();

    void priceChanged();

    void durationChanged();

private:
    int m_id;
    QString m_subscriptionName;
    double m_price;
    int m_duration;
};

#endif // SUBSCRIPTION_TYPE_H
