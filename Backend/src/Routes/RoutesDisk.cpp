#include <iostream>
#include <map>
#include <cstring>
#include <vector>
#include "../Objects/CommandResult.h"
#include "../Controllers/ControllerDisk.h"
#include "./RoutesDisk.h"

using namespace std;

vector<CommandResult> RoutesDisk::mkdisk(const map<string, string>& params){
    vector<CommandResult> results;
    if(params.find("size") == params.end()){
        
    }
    else if(params.find("path") == params.end()){
        results.push_back({false, "Mkdisk: Missing parameter -path"});
        return results;
    }
    
    //The mandatory parameters are obtained
    string path = "Disks/" + params.at("path");
    int size;
    try{ size = stoi(params.at("size")); }
    catch(...){
        results.push_back({false, "Mkdisk: Invalid value for size of the disk"});
        return results;
    }
    if(size < 1){
        results.push_back({false, "Mkdisk: The size must be a positive size"});
        return results;
    }
    
    //Optional parameters
    char fit = 'f';
    if(params.find("fit") != params.end()) fit = params.at("fit")[0];
    if(fit != 'b' && fit != 'f' && fit != 'w'){
        results.push_back({false, "Mkdisk: Invalid value for fit"});
        return results;
    }

    string unit = "m";
    if(params.find("unit") != params.end()) unit = params.at("unit");
    if(unit != "m" && unit != "k"){
        results.push_back({false, "Mkdisk: Invalid value for unit"});
        return results;
    }
    if(unit == "k") size *= 1024;
    else size *= 1024*1024;
    
    return ControllerDisk::createDisk(path, fit, size);
}

CommandResult RoutesDisk::rmdisk(const map<string, string>& params){
    if(params.find("path") == params.end()) return {false, "Rmdisk: Missing parameter -path"};
    string path = "Disks/" + params.at("path");
    return ControllerDisk::deleteDisk(path);
}