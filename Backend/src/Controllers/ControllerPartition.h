#ifndef CONTROLLERPARTITION_H_INCLUDED
#define CONTROLLERPARTITION_H_INCLUDED

#include <string>
#include "../Objects/CommandResult.h"

class ControllerPartition{
    public:
        static CommandResult createPartition(const std::string& path, char& type, int& size, char& fit, char* name);
        static CommandResult mountPartition(const std::string& path, char* name);
};

#endif
