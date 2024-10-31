#pragma once

#include <QString>

class NetworkCommand {
public:
    virtual ~NetworkCommand() = default;
    virtual void execute() = 0;
    virtual QString typeName() const = 0;
};
