#pragma once

#include <exception>

class max_task_exception : public std::exception
{
public:
    const char* what() const noexcept override;
};
