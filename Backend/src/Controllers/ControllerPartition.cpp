#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <cstring>
#include <fstream>
#include "../Objects/CommandResult.h"
#include "../Objects/MBR.h"
#include "../Objects/Partition.h"
#include "./ControllerDisk.h"
#include "./ControllerPartition.h"
#include "./Utilities.h"

using namespace std;

bool partitionCounter(MBR& mbr, char typePartition){
    int primary = 0;
    int extended = 0;
    for(const Partition& currentPartition: mbr.partitions){
        if(currentPartition.part_start != -1){
            if(currentPartition.part_type == 'p') primary++;
            else if(currentPartition.part_type == 'e') extended++;
        }
    }
    if(typePartition == 'p' && primary >= 3) return false;
    else if(typePartition == 'e' && extended >= 1) return false;
    return true;
}

vector<Partition> getActiveAndSort(const MBR& mbr){
    vector<Partition> activePartitions;
    
    for(const Partition& currentPartition: mbr.partitions){
        if(currentPartition.part_start != -1) activePartitions.push_back(currentPartition);
    }

    sort(activePartitions.begin(), activePartitions.end(),
    [](const Partition& a, const Partition& b){
        return a.part_start < b.part_start;
    });

    return activePartitions;
}

int firstFit(const MBR& mbr, int size){
    int start = sizeof(MBR);
    vector<Partition> activePartitions = getActiveAndSort(mbr);

    for (const Partition& partition : activePartitions){
        //available space between partitions
        if (partition.part_start - start >= size) return start;
        //The point is modev to the end of the partition
        start = partition.part_start + partition.part_s;
    }
    //The space at the end of the disk is checked
    //Unique scenario when creating the first partition
    if (mbr.mbr_size - start >= size) return start;

    return -1;
}

int bestFit(const MBR& mbr, int size){
    int start = sizeof(MBR);
    int bestStart = -1;
    int smallestSpace = mbr.mbr_size;
    vector<Partition> activePartitions = getActiveAndSort(mbr);

    for (const Partition& currentPartition : activePartitions){
        //avaliable space between partitions
        int freeSpace = currentPartition.part_start - start;
        if (freeSpace >= size && freeSpace < smallestSpace){
            //The space is enough to accommodate the partition
            //The space current space becomes the smallest one
            smallestSpace = freeSpace;
            bestStart = start;
        }
        start = currentPartition.part_start + currentPartition.part_s;
    }
    //The space at the end of the disk is checked
    //End of the disk and last point to start
    int freeSpace = mbr.mbr_size - start;
    if (freeSpace >= size && freeSpace < smallestSpace){
        //smallestSpace = freeSpace;
        bestStart = start;
    }

    return bestStart;
}

int worstFit(const MBR& mbr, int size){
    int start = sizeof(MBR);
    int biggestSpace = 0;
    int bestStart = -1;
    vector<Partition> activePartitions = getActiveAndSort(mbr);

    for (const Partition& currentPartition : activePartitions){
        //avaliable space between partitions
        int freeSpace = currentPartition.part_start - start;
        if (freeSpace >= size && freeSpace > biggestSpace){
            biggestSpace = freeSpace;
            bestStart = start;
        }
        start = currentPartition.part_start + currentPartition.part_s;
    }
    //space at the end of the disk
    int freeSpace = mbr.mbr_size - start;
    if (freeSpace >= size && freeSpace > biggestSpace){
        //biggestSpace = freeSpace;
        bestStart = start;
    }
    return bestStart;
}

CommandResult ControllerPartition::createPartition(const string& path, char& type, int& size, char& fit, char* name){
    if(!ControllerDisk::diskExist(path)) return {false, "Fdisk: The disk was not found"};
    
    MBR mbr = ControllerDisk::readMBR(path);
    if(!partitionCounter(mbr, type)) return {false, "Fdisk: The disk capacity for a partition [" + string(type, 1) + "] has been reached"};

    int byteStart;
    if(fit == 'b') byteStart = bestFit(mbr, size);
    else if(fit == 'f') byteStart = firstFit(mbr, size);
    else byteStart = worstFit(mbr, size);
    if(byteStart == -1) return {false, "Fdisk: The space for the partition is not enough"};

    //A free partition sought
    Partition* partition = nullptr;
    int correlative = 1;
    bool partitionFound = false;
    for(int i = 0; i < 4; i++){
        if(strncmp(mbr.partitions[i].part_name, name, 15) == 0) return {false, "Fdisk: The name [" + string(name) + "] has already been taken"};
        if(partitionFound == false && mbr.partitions[i].part_start == -1){
            partition = &mbr.partitions[i];
            correlative = i;
            partitionFound = true;
        }
    }

    if (partition == nullptr) return {false, "Fdisk: There are no free partition entries in the MBR"};
    //The data for the partition is assigned
    //status and doesnt change
    partition->part_type = type;
    partition->part_fit = fit;
    partition->part_start = byteStart;
    partition->part_s = size;
    strncpy(partition->part_name, name, 15);
    partition->part_name[15] = '\0';
    partition->part_correlative = correlative;
    memset(partition->part_id, '0', 4);         //The initial id is 0000 
    ControllerDisk::writeMBR(path, mbr);
    return {true, "Fdisk: The partition has been created succesfully"};
}