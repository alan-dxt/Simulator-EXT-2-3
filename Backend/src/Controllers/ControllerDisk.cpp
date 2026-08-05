#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <vector>
#include "../Objects/MBR.h"
#include "../Objects/CommandResult.h"
#include "./ControllerDisk.h"
#include "./ControllerSystem.h"
#include "./ControllerGlobal.h"
#include "./Utilities.h"

using namespace std;
//ios::out | ios::binary    ->  CREATES
//ios::in | ios::binary     ->  READ
//ios::in | ios::out | ios::binary      ->  MODIFIES
//ios::out | ios::binary    ->  DELETES THEN WRITE

void ControllerDisk::writeMBR(const string& path, MBR& mbr){
    fstream file(path, ios::in  | ios::out | ios::binary);
    file.seekg(0);
    file.write((char*)&mbr, sizeof(MBR));
    file.close();
}

MBR ControllerDisk::readMBR(const string& path){
    fstream file(path, ios::in | ios:: out | ios::binary);
    MBR mbr;
    file.seekg(0);
    file.read((char*)&mbr, sizeof(MBR));
    file.close();
    return mbr;
}

vector<CommandResult> ControllerDisk::createDisk(const string& path, char& fit, int& size){
    vector<CommandResult> results;
    int counter;
    if(Utilities::diskExist(path)){
        results.push_back({false, "Mkdisk: The disk already exists"});
        return results;
    }
    
    //The paths are checked first
    //Deletes invalid paths and checks the amount of disks
    vector<CommandResult> newResults = ControllerSystem::cleanRegisteredPaths(counter);
    if(counter >= 52){
        results.push_back({false, "Mkdisk: The limit number of disks has been reached(52)"});
        return results;
    }
    results.insert(
        results.end(),
        make_move_iterator(newResults.begin()),
        make_move_iterator(newResults.end())
    );

    //Disk registration must occur prior to creation
    results.push_back(ControllerSystem::registerPath(path));

    //Creating the disk
    fstream file(path, ios::out | ios::binary);
    file.seekp(size -1);
    file.put('\0');
    file.close();
    //creating the mbr
    MBR mbr{};
    mbr.mbr_size = size;
    mbr.dsk_fit = fit;
    mbr.mbr_date = time(nullptr);
    mbr.mbr_dsk_signatire = rand();
    for(int i = 0; i < 4; i++){
        Partition& currentPartition = mbr.partitions[i];
        currentPartition.part_status = 'f';
        currentPartition.part_name[0] = '-';
        currentPartition.part_id[0] = '-';
        currentPartition.part_type = '-';
        currentPartition.part_fit = '-';
        currentPartition.part_start = -1;
        currentPartition.part_s = -1;
        currentPartition.part_correlative = -1;
    }
    writeMBR(path, mbr);
    results.push_back({true, "Mkdisk: The disk was created succesfully"});
    return results;
}

vector<CommandResult> ControllerDisk::deleteDisk(const string& path){
    vector<CommandResult> results;
    results.push_back(ControllerSystem::deletePath(path));
    ControllerGlobal::deleteMountedPartitionMemory(path);
    if(!Utilities::diskExist(path)){
        results.push_back({false, "Rmdisk: The disk was not found"});
        return results;
    }
    if(filesystem::remove(path)){
        results.push_back({true, "Rmdisk: The disk was removed succesfully"});
        return results;
    }
    results.push_back({false, "Rmdisk: It was not possible to delete the disk"});
    return results;
}
