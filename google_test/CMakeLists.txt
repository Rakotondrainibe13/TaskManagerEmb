cmake_minimum_required(VERSION 3.10)

set(this google_test)
project(${this} CXX)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(googletest)

# Set the path to your Qt installation
set(QT_PATH /opt/Qt/6.7.2/gcc_64)

# Find the required Qt packages
set(CMAKE_PREFIX_PATH ${QT_PATH})
find_package(Qt6 REQUIRED COMPONENTS Core Sql Quick Test)
find_package(Qt6 REQUIRED COMPONENTS Core Sql Quick Test)

# Include Qt directories
# Where the compiler should look for header files
include_directories(
    ${Qt6Core_INCLUDE_DIRS}
    ${Qt6Sql_INCLUDE_DIRS} 
    ${Qt6Quick_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/../src/include
)

# Use automoc to process headers for Qt's meta-object system
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(Headers
    ../src/include/task_factory.h
    ../src/include/simple_task.h
    ../src/include/project_task.h
    ../src/include/recurring_task.h
    ../src/include/task.h
    ../src/include/security_manager.h
    ../src/include/database_manager.h
    ../src/include/encryption_strategy.h
    ../src/include/open_connection_command.h
    ../src/include/close_connection_command.h
    ../src/include/send_data_command.h
    ../src/include/udp_send_command.h
    ../src/include/receive_data_command.h
    ../src/include/network_log.h
    ../src/include/network_monitor.h
    ../src/include/network_config.h
    ../src/include/network_command.h
    ../src/include/network_manager.h
    ../src/include/subscription.h
    ../src/include/subscription_type.h
    ../src/taskExecution/simple_execution_strategy.h
    ../src/taskExecution/parallel_execution_strategy.h
    ../src/taskExecution/sequential_execution_strategy.h
    ../src/taskExecution/prioritized_execution_strategy.h
    ../src/notification/notification.h
    ../src/include/task_observer.h
    ../src/include/user.h
    ../src/report/productivityReport.h
    ../src/include/encryption_service.h
    ../src/include/ssh_manager.h
    ../src/include/exception_manager.h
    ../src/include/synch_manager.h
    ../src/include/synch_config.h

)

set(Sources
    ../src/src/task_factory.cpp
    ../src/src/simple_task.cpp
    ../src/src/project_task.cpp
    ../src/src/recurring_task.cpp
    ../src/src/task.cpp
    ../src/manager/security_manager.cpp
    ../src/manager/database_manager.cpp
    ../src/network/open_connection_command.cpp
    ../src/network/close_connection_command.cpp
    ../src/network/send_data_command.cpp
    ../src/network/receive_data_command.cpp
    ../src/network/udp_send_command.cpp
    ../src/network/network_log.cpp
    ../src/network/network_monitor.cpp
    ../src/network/network_config.cpp
    ../src/manager/network_manager.cpp
    ../src/notification/notification.cpp
    ../src/src/user.cpp
    ../src/subscription/subscription.cpp
    ../src/subscription/subscription_type.cpp
    ../src/taskExecution/simple_execution_strategy.cpp
    ../src/taskExecution/parallel_execution_strategy.cpp
    ../src/taskExecution/sequential_execution_strategy.cpp
    ../src/taskExecution/prioritized_execution_strategy.cpp
    ../src/report/productivityReport.cpp
    ../src/encryptage/encryption_service.cpp
    ../src/manager/ssh_manager.cpp
    ../src/manager/synch_manager.cpp
    ../src/manager/synch_config.cpp

)

add_library(${this} STATIC ${Sources} ${Headers})

# Link with Qt libraries
target_link_libraries(${this}
    Qt6::Core
    Qt6::Sql
    Qt6::Quick
)

add_subdirectory(unit_test)
