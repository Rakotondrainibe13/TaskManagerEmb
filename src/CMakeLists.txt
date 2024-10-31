cmake_minimum_required(VERSION 3.10)

project(TaskManagerEmb VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(SOURCES
    main.cpp 
    controllers/main_controller.cpp
    src/task.cpp
    taskExecution/simple_execution_strategy.cpp
    taskExecution/parallel_execution_strategy.cpp
    taskExecution/prioritized_execution_strategy.cpp
    taskExecution/sequential_execution_strategy.cpp
    taskExecution/qt_concurrent_async_execution.cpp
    taskExecution/qthreadpool_async_execution.cpp
    taskExecution/timer_based_async_execution.cpp
    src/simple_task.cpp
    src/recurring_task.cpp
    src/project_task.cpp
    src/task_factory.cpp

    manager/database_manager.cpp
    manager/task_manager.cpp
    src/form_validator.cpp
    mapper/task_mapper.cpp
    mapper/user_mapper.cpp

    network/network_log.cpp
    network/network_monitor.cpp
    network/network_config.cpp
    controllers/network_config_controller.cpp
    network/open_connection_command.cpp
    network/receive_data_command.cpp
    network/close_connection_command.cpp
    network/send_data_command.cpp
    network/udp_send_command.cpp
    manager/network_manager.cpp
    manager/synch_manager.cpp
    manager/ssh_manager.cpp

    encryptage/encryption_service.cpp
    
    manager/security_manager.cpp
    src/aesencryption_strategy.cpp
    tests/network_test.cpp 
    tests/form_validator_test.cpp
    manager/notification_manager.cpp
    manager/authorization_manager.cpp
    manager/user_manager.cpp
    iterator/task_iterator.cpp
    mapper/projet_task_mapper.cpp

    calendar/eventmodel.cpp
    notification/notification.cpp
    src/task_observer.cpp
    src/user.cpp
    subscription/subscription_type.cpp
    subscription/subscription.cpp
    manager/subscription_manager.cpp
    subscription/subscription_factory.cpp
    subscription/monthly_subscription_factory.cpp
    subscription/yearly_subscription_factory.cpp
    subscription/montly_subscription.cpp
    subscription/yearly_subscription.cpp

    profiler/profiler.cpp
    report/productivityReport.cpp

    statistics/statistics_manager.cpp
    statistics/statistics_subject.cpp
    statistics/statistics_model.cpp
    mapper/subscription_mapper.cpp
    src/max_task_exception.cpp

    manager/synch_manager.cpp
    manager/ssh_manager.cpp
    encryptage/encryption_service.cpp
    manager/synch_config.cpp
    mapper/task_list_model.cpp
)

set(HEADERS
    controllers/main_controller.h
    controllers/navigation_controller.h
    taskExecution//itask_execution_strategy.h
    taskExecution/simple_execution_strategy.h
    taskExecution/sequential_execution_strategy.h
    taskExecution/parallel_execution_strategy.h
    taskExecution/prioritized_execution_strategy.h
    taskExecution/iasync_task_execution.h
    taskExecution/qt_concurrent_async_execution.h
    taskExecution/qthreadpool_async_execution.h
    taskExecution/timer_based_async_execution.h
    include/simple_task.h
    include/recurring_task.h
    include/project_task.h
    include/task_factory.h  
    include/task.h
    include/task_manager.h    
    include/database_manager.h
    include/security_manager.h
    include/network_manager.h
    include/task_observer.h
    taskExecution/itask_execution_strategy.h
    include/form_validator.h
    include/imodel_mapper.h
    include/task_mapper.h
    include/network_log.h
    include/network_monitor.h
    include/network_config.h
    include/network_command.h
    controllers/network_config_controller.h
    include/open_connection_command.h
    include/receive_data_command.h
    include/close_connection_command.h
    include/send_data_command.h
    include/udp_send_command.h
    include/aesencryption_strategy.h
    include/encryption_strategy.h
    include/notification_manager.h
    include/projet_task_mapper.h

    include/authorization_manager.h
    include/user.h
    include/user_manager.h
    include/user_mapper.h

    include/synch_manager.h
    include/ssh_manager.h
    include/encryption_service.h

    calendar/eventmodel.h
    
    tests/network_test.h
    tests/form_validator_test.h
    #iterator/task_iterator.h
    notification/notification.h

    include/subscription_type.h
    include/subscription.h
    include/subscription_manager.h
    include/subscription_factory.h
    include/monthly_subscription_factory.h
    include/yearly_subscription_factory.h
    include/montly_subscription.h
    include/yearly_subscription.h

    profiler/profiler.h
    
    report/report_template.h
    report/productivityReport.h

    statistics/statistics_manager.h
    statistics/statistics_observer.h
    statistics/statistics_subject.h
    statistics/statistics_model.h

    include/subscription_mapper.h
    include/max_task_exception.h

    include/synch_manager.h
    include/ssh_manager.h
    include/encryption_service.h
    include/synch_config.h
    include/exception_manager.h
    include/task_list_model.h
)


find_package(Qt6 REQUIRED COMPONENTS Charts Core Gui Qml Sql Quick Test Concurrent)

# include_directories(${Qt6Sql_INCLUDE_DIRS})
include_directories(${Qt6Core_INCLUDE_DIRS} ${Qt6Sql_INCLUDE_DIRS} ${Qt6Quick_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR} calendar)
qt_standard_project_setup()

qt_add_resources(SOURCES qml/components.qrc qml/assets.qrc qml/views.qrc)
qt_add_executable(appTaskManagerEmb
    ${SOURCES}
    ${HEADERS}
)

qt_add_qml_module(appTaskManagerEmb
    URI App
    QML_FILES
        qml/components/MonthGridDelegate.qml
        qml/views/EventCalendar.qml
    RESOURCES
        qtquickcontrols2.conf
    NO_RESOURCE_TARGET_PATH
)
# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appTaskManagerEmb PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appTaskManagerEmb
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appTaskManagerEmb 
    PRIVATE Qt6::Core Qt6::Sql Qt6::Quick Qt6::Test Qt6::Charts Qt6::Concurrent

)

# qt_generate_deploy_qml_app_script(
#     TARGET appTaskManagerEmb
#     OUTPUT_SCRIPT deploy_script
#     MACOS_BUNDLE_POST_BUILD
#     NO_UNSUPPORTED_PLATFORM_ERROR
#     DEPLOY_USER_QML_MODULES_ON_UNSUPPORTED_PLATFORM
# )
# install(SCRIPT ${deploy_script})

include(GNUInstallDirs)
install(TARGETS appTaskManagerEmb
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

set(CMAKE_AUTOMOC ON)
enable_testing()
add_test(NAME FormValidatorTest COMMAND FormValidatorTest)

install(FILES qmldir DESTINATION ${CMAKE_INSTALL_PREFIX}/qml/)


# add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})
