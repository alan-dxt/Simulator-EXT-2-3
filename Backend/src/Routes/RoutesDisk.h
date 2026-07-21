#ifndef ROUTESDISK_H_INCLUDED
#define ROUTESDISK_H_INCLUDED

#include <string>
#include <map>
#include "../Objects/CommandResult.h"

class RoutesDisk{
    public:
        static CommandResult mkdisk(const std::map<std::string, std::string>& params);
        static CommandResult rmdisk(const std::map<std::string, std::string>& params);
};

#endif