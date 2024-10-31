// sample_test.cpp
#include <gtest/gtest.h>
#include <QCoreApplication>
#include "include/task_factory_test.h"
#include "include/security_manager_test.h"
#include "include/network_manager_test.h"
#include "include/task_execution_strategy_test.h"
#include "include/productivity_report_test.h"
#include "include/synch_manager_test.h"
int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
