#pragma once
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <memory>

class NetworkTest : public QObject
{
    Q_OBJECT
public:
    explicit NetworkTest(QObject *parent = nullptr);
    void testConnectivity() const;

private slots:
    void onFinished(QNetworkReply *reply);

private:
    std::unique_ptr<QNetworkAccessManager> m_manager;
};
