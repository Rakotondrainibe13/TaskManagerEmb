#include "network_test.h"

#include <QNetworkRequest>
#include <QUrl>
#include <QDebug>

NetworkTest::NetworkTest(QObject *parent) : QObject(parent), m_manager(new QNetworkAccessManager(this))
{
    // check if networkManager is created successfuly
    Q_ASSERT(m_manager.get());
    connect(m_manager.get(), &QNetworkAccessManager::finished, this, &NetworkTest::onFinished);
}

void NetworkTest::testConnectivity() const
{
    QNetworkRequest request(QUrl("http://www.example.com"));
    m_manager->get(request);
}

void NetworkTest::onFinished(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        qDebug() << "Connectivity test succeeded.";
    }
    else
    {
        qDebug() << "Connectivity test failed: " << reply->errorString();
    }
    reply->deleteLater();
}
