#ifndef CONTROLLERSYSTEM_H_INCLUDED
#define CONTROLLERSYSTEM_H_INCLUDED

#include <vector>
#include <string>
#include "../Objects/CommandResult.h"

class ControllerSystem{
    public:
        static bool isValidPathLine(const std::string& path);
        static CommandResult registerPath(const std::string& path);
        static std::vector<CommandResult> cleanRegisteredPaths(int& counter);
};

#endif