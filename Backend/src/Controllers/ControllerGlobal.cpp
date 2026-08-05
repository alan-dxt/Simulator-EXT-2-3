#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>
#include "./ControllerGlobal.h"
#include "./ControllerDisk.h"
#include "./Utilities.h"
#include "../Objects/Mount.h"
#include "../Objects/CommandResult.h"

using namespace std;

vector<Mount> ControllerGlobal::mountedPartitions{};
string ControllerGlobal::currentDisk = "";
Mount ControllerGlobal::currentMountedPartition{};

void ControllerGlobal::addMountedPartition(const string& path, int& start, char* id, char* name){
    Mount mount{};
    mount.path = path;
    mount.start = start;
    strncpy(mount.id, id, 4);
    strncpy(mount.name, name, 15);
    ControllerGlobal::mountedPartitions.push_back(mount);
}

Mount* ControllerGlobal::getMountedPartition(const char* id){
    for(Mount& currentPartition: ControllerGlobal::mountedPartitions){
        if(strncmp(currentPartition.id, id, 4) == 0) return &currentPartition;
    }
    return nullptr;
}

//Delete the partitions from memory when deleting a disk
void ControllerGlobal::deleteMountedPartitionMemory(const std::string& path) {
    for (auto it = ControllerGlobal::mountedPartitions.begin();
        it != ControllerGlobal::mountedPartitions.end(); ) {
        if (it->path == path) {
            it = ControllerGlobal::mountedPartitions.erase(it);
        } else {
            ++it;
        }
    }
}