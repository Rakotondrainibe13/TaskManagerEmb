#pragma once
#include "../../../src/include/task_factory.h"
#include "../../../src/include/simple_task.h"
#include "../../../src/include/project_task.h"
#include "../../../src/include/recurring_task.h"


TEST(TaskFactoryTest, CreatesSimpleTask) {
    TaskPtr task = TaskFactory::createTask(TaskFactory::TaskType::Simple, "Simple Task", Task::Priority::Low);
    EXPECT_TRUE(task != nullptr);
    EXPECT_EQ(task->getTitle(), "Simple Task");
    EXPECT_EQ(task->getPriority(), Task::Priority::Low);
}

TEST(TaskFactoryTest, CreatesRecurringTask) {
    TaskPtr task = TaskFactory::createTask(TaskFactory::TaskType::Recurring, "Recurring Task", Task::Priority::Medium);
    EXPECT_TRUE(task != nullptr);
    EXPECT_EQ(task->getTitle(), "Recurring Task");
    EXPECT_EQ(task->getPriority(), Task::Priority::Medium);
}

TEST(TaskFactoryTest, CreatesProjectTask) {
    TaskPtr task = TaskFactory::createTask(TaskFactory::TaskType::Project, "Project Task", Task::Priority::High);
    EXPECT_TRUE(task != nullptr);
    EXPECT_EQ(task->getTitle(), "Project Task");
    EXPECT_EQ(task->getPriority(), Task::Priority::High);
}

TEST(TaskFactoryTest, ThrowsInvalidArgumentOnUnknownType) {
    EXPECT_THROW(TaskFactory::createTask(static_cast<TaskFactory::TaskType>(-1), "Unknown Task", Task::Priority::Low), std::invalid_argument);
}

