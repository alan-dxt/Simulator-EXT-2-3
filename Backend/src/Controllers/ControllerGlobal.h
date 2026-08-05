#ifndef CONTROLLERGLOBAL_H_INCLUDED
#define CONTROLLERGLOBAL_H_INCLUDED

#include <vector>
#include "../Objects/CommandResult.h"
#include "../Objects/Mount.h"

class ControllerGlobal{
    public:
        //Global data
        static std::vector<Mount> mountedPartitions;
        static std::string currentDisk;
        static Mount currentMountedPartition;
        //functions and methods
        static void addMountedPartition(const std::string& path, int& start, char* id, char* name);
        static Mount* getMountedPartition(const char* id);
        static void deleteMountedPartitionMemory(const std::string& path);
};

#endif