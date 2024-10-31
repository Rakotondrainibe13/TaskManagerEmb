#ifndef TASK_EXECUTION_STRATEGY_TEST_H
#define TASK_EXECUTION_STRATEGY_TEST_H

#include "../../../src/taskExecution/simple_execution_strategy.h"
#include "../../../src/taskExecution/parallel_execution_strategy.h"
#include "../../../src/taskExecution/sequential_execution_strategy.h"
#include "../../../src/taskExecution/prioritized_execution_strategy.h"
#include "../../../src/include/project_task.h"


TEST(TaskExecutionStrategyTest, SimpleExecutionStrategy) {
    TaskExecution::SimpleExecutionStrategy strategy;

    int status=1;
    Task* task= new Task();
    task->setStatus(static_cast<Task::Status>(0));
    strategy.execute(task);
    EXPECT_TRUE(task != nullptr);
    EXPECT_EQ(static_cast<int>(task->getStatus()), status);
    delete task;
}

TEST(TaskExecutionStrategyTest, ParallelExecutionStrategy) {
    TaskExecution::ParallelExecutionStrategy strategy;

    int status=1;
    Task* task= new ProjectTask("test Task");
    task->setStatus(static_cast<Task::Status>(0));
    strategy.execute(task);
    EXPECT_TRUE(task != nullptr);
    EXPECT_EQ(static_cast<int>(task->getStatus()), status);
    delete task;
}

TEST(TaskExecutionStrategyTest, SequentialExecutionStrategy) {
    TaskExecution::SequentialExecutionStrategy strategy;

    int status=1;
    Task* task= new ProjectTask("test Task");
    task->setStatus(static_cast<Task::Status>(0));
    strategy.execute(task);
    EXPECT_TRUE(task != nullptr);
    EXPECT_EQ(static_cast<int>(task->getStatus()), status);
    delete task;
}

TEST(TaskExecutionStrategyTest, PrioritizedExecutionStrategy) {
    TaskExecution::PrioritizedExecutionStrategy strategy;

    int status=1;
    Task* task= new ProjectTask("test Task");
    task->setStatus(static_cast<Task::Status>(0));
    strategy.execute(task);
    EXPECT_TRUE(task != nullptr);
    EXPECT_EQ(static_cast<int>(task->getStatus()), status);
    delete task;
}
#endif // TASK_EXECUTION_STRATEGY_TEST_H
