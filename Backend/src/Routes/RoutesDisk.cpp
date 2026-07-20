#include <iostream>
#include <map>
#include <cstring>
#include "../Objects/CommandResult.h"
#include "../Controllers/ControllerDisk.h"
#include "./RoutesDisk.h"

using namespace std;

CommandResult RoutesDisk::mkdisk(const map<string, string>& params){
    if(params.find("size") == params.end()) return {false, "Mkdisk: Missing parameter -size"};
    if(params.find("path") == params.end()) return {false, "Mkdisk: Missing parameter -path"};
    
    //The mandatory parameters are obtained
    std::string path = std::string("Disks/") + params.at("path");
    int size;
    try{ size = stoi(params.at("size")); }
    catch(...){return {false, "Mkdisk: Invalid value for size"};}
    
    //Optional parameters
    char fit = 'f';
    if(params.find("fit") != params.end()) fit = params.at("fit")[0];
    if(fit != 'b' && fit != 'f' && fit != 'w') return {false, "Mkdisk: Invalid value for fit"};

    string unit = "m";
    if(params.find("unit") != params.end()) unit = params.at("unit");
    if(unit != "m" && unit != "k") return {false, "Mkdisk: Invalid value for unit"};
    if(unit == "k") size *= 1024;
    else size *= 1024*1024;
    
    return ControllerDisk::createDisk(path, fit, size);
}