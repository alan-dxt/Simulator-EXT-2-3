#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include "../Objects/MBR.h"
#include "../Objects/CommandResult.h"
#include "./ControllerDisk.h"

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

bool ControllerDisk::diskExist(const string& path){
    ifstream file(path, std::ios::binary);
    return file.good();
}

CommandResult ControllerDisk::createDisk(const string& path, char& fit, int& size){
    if(diskExist(path)) return {false, "Mkdisk: The disk already exists"};
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
    return {false, "Mkdisk: The disk was created succesfully"};
}

CommandResult ControllerDisk::deleteDisk(const string& path){
    if(!diskExist(path)) return {false, "Rmdisk: The disk was not found"};
    if(filesystem::remove(path)) return {true, "Rmdisk: The disk was removed succesfully"};
    return {false, "Rmdisk: It was not possible to delete the disk"};
}
