#include <QApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <QQmlContext>

#include "controllers/main_controller.h"
#include "controllers/network_config_controller.h"
#include "include/network_manager.h"
#include "include/task_manager.h"
#include "tests/network_test.h"
#include "include/form_validator.h"
#include "statistics/statistics_model.h"
#include "notification/notification.h"

static QObject* formValidatorSingletonProvider(QQmlEngine* engine, QJSEngine* scriptEngine) {
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)
    return new FormValidator();  // Singleton instance
}
int main(int argc, char *argv[])
{
    const int WINDOW_WIDTH (1024);

    const int WINDOW_HEIGHT (658);

	QApplication app(argc, argv);

    qmlRegisterType<NetworkConfigController>("Controllers", 1, 0, "NetworkConfigController");
    qmlRegisterType<TaskManager>("Controllers", 1, 0, "TaskManager");

    NetworkTest networkTest;
    networkTest.testConnectivity();

    QQmlApplicationEngine engine;
    engine.addImportPath("qrc:/");

    controllers::MainController mainController;

    //qmlRegisterType<controllers::MainController>("mainController", 1, 0, "MainController");

    NetworkManager &networkManager = NetworkManager::instance();
    engine.rootContext()->setContextProperty("networkManager", &networkManager);

    engine.rootContext()->setContextProperty("mainController", &mainController);

    engine.rootContext()->setContextProperty("WINDOW_WIDTH", WINDOW_WIDTH);
    engine.rootContext()->setContextProperty("WINDOW_HEIGHT", WINDOW_HEIGHT);

    StatisticsModel statsModel;
    engine.rootContext()->setContextProperty("statistics_model", &statsModel);

    const QUrl url(u"qrc:/views/Main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
                         if (!obj && url == objUrl)
                            QCoreApplication::exit(-1);
                     }, Qt::QueuedConnection);
    engine.load(url);



    // Notification* notification = new Notification();
    // notification->setUserId(2);
    // notification->setTaskId(17);
    // notification->setMessage("Another message");
    // notification->setIsRead(true);
    // notification->setType(Notification::NotificationType::TaskCreated);

    // std::shared_ptr<DatabaseManager> db = DatabaseManager::instance();
    // auto saving = db->saveNotification(notification);
    // qDebug() << "saving is : " << saving;

    // delete notification;
    return app.exec();
}
