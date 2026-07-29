#ifndef ROUTESPARTITION_H_INCLUDED
#define ROUTESPARTITION_H_INCLUDED

#include <map>
#include <string>
#include "../Objects/CommandResult.h"

class RoutesPartition{
    public:
        static CommandResult fdisk(const std::map<std::string, std::string>& params);
};

#endif