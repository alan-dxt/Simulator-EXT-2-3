#include <iostream>
#include <map>
#include <cstring>
#include "./RoutesPartition.h"
#include "../Objects/CommandResult.h"
#include "../Controllers/ControllerPartition.h"

using namespace std;

CommandResult RoutesPartition::fdisk(const map<string, string>& params){
    if(params.find("size") == params.end()) return {false, "Fdisk: Missing parameter -size"};
    if(params.find("path") == params.end()) return {false, "Fdisk: Missing parameter -path"};
    if(params.find("name") == params.end()) return {false, "Fdisk: Missing parameter -name"};

    //Mandatory parameters
    string path = "Disks/" + params.at("path");
    
    if(params.at("name").length() > 15) return {false, "Fdisk: The name cannot exceed 15 characteres"};
    char name[15];
    strncpy(name, params.at("name").c_str(), 15);
    //cout<<"The name is: ["<<name<<"]\n";
    
    int size;
    try{ size = stoi(params.at("size")); }
    catch(...) { return {false, "Fdisk: Invalid value for the size of the partition"}; }
    if(size < 1) return {false, "Fdisk: The size must be a positive value"};

    //Optional parameters
    char unit = 'k';
    if(params.find("unit") != params.end()) unit = params.at("unit")[0];
    if(unit != 'b' && unit != 'k' && unit != 'm') return {false, "Fdisk: Invalid value for unit"};
    if(unit == 'k') size *= 1024;
    else if(unit == 'm') size *= 1024 * 1024;

    char type = 'p';
    if(params.find("type") != params.end()) type = params.at("type")[0];
    if(type != 'p' && type != 'e' && type != 'l') return {false, "Fdisk: Invalid value for type"};

    char fit = 'w';
    if(params.find("fit") != params.end()) fit = params.at("fit")[0];
    if(fit != 'b' && fit != 'f' && fit != 'w') return {false, "Fdisk: Invalid value for fit"};

    return ControllerPartition::createPartition(path, type, size, fit, name);
}