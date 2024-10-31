cmake_minimum_required(VERSION 3.10)

set(this unit_test)
project(${this} CXX)

set(Sources
    main_test.cpp
)

set(Headers
    include/task_factory_test.h
    include/synch_manager_test.h
    include/security_manager_test.h
    include/network_manager_test.h
    include/task_execution_strategy_test.h
    include/productivity_report_test.h
)

# Find Google Test
# find_package(GTest REQUIRED)
set(CMAKE_PREFIX_PATH /opt/Qt/6.7.2/gcc_64)
add_executable(${this} ${Sources} ${Headers})

target_link_libraries(${this} PUBLIC
    GTest::gtest_main
    GTest::gtest 
    GTest::gmock_main
    GTest::gmock
    Qt6::Test
    Qt6::Core
    Qt6::Sql
    Qt6::Quick
    google_test
    )





# Enable testing
enable_testing()

# Add test
add_test(
    NAME ${this}
    COMMAND ${this}
)
