#ifndef NAVIGATION_CONTROLLER_H
#define NAVIGATION_CONTROLLER_H
#include <QObject>

class NavigationController : public QObject
{

    Q_OBJECT

public:
    explicit NavigationController(QObject *parent = nullptr) : QObject(parent) {}
signals:
    void goCreateTaskScreen();
    void goListTaskScreen();
    void goEditTaskScreen(const int& id);
    void goNetworkConfigScreen();
    void goRetentionConfigScreen();
    void goNetworkMonitoringScreen();
    void goNetworkLogScreen();
    void goLoginScreen();
    void goNotificationScreen();
    void goUserScreen();
    void goCalendarScreen();
    void goStatisticScreen();
    void goDetailTaskScreen(const int& id);
    void goSubscriptionStateScreen();
    void goSubscriptionCreateScreen();
    void goSubscriptionDetailScreen(const int& id);
};

#endif // NAVIGATION_CONTROLLER_H
