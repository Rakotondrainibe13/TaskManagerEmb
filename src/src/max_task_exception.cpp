#include "../include/max_task_exception.h"

const char* max_task_exception::what() const noexcept {
    return "The maximum number of tasks has been reached for the free plan. Do you want to subscribe ?";
}
