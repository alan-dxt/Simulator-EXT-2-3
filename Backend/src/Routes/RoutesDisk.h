#ifndef ROUTESDISK_H_INCLUDED
#define ROUTESDISK_H_INCLUDED

#include <string>
#include <map>
#include <vector>
#include "../Objects/CommandResult.h"

class RoutesDisk{
    public:
        static std::vector<CommandResult> mkdisk(const std::map<std::string, std::string>& params);
        static std::vector<CommandResult> rmdisk(const std::map<std::string, std::string>& params);
};

#endif