#include <iostream>
#include <fstream>
#include "./ControllerSystem.h"
#include "./Utilities.h"
#include "../Objects/CommandResult.h"

using namespace std;

bool ControllerSystem::isValidPathLine(const string& line) {
    //Firt character between: a-z & A-Z
    char id = line[0];
    if (!((id >= 'a' && id <= 'z') || (id >= 'A' && id <= 'Z'))) return false;

    //Second character "comma"
    if (line[1] != ',')return false;

    //Mandatory extention
    const std::string extention = ".mia";
    if (line.substr(line.size() - extention.size()) != extention) return false;

    //At lest one character before the extention ".mia"
    if (line.size() == 2 + extention.size()) return false;

    return true;
}

vector<CommandResult> ControllerSystem::cleanRegisteredPaths(int& counter){
    counter = 0;
    vector<CommandResult> results;
    string paths = "Disks/Paths.txt";
    string newContent = "";                 //New content in case an error
    bool change = false;                    //Error confirmation
    string line;
    if(!Utilities::diskExist(paths)){
        fstream file(paths, ios::out | ios::binary);
        file.close();
        return results;
    }
    fstream file(paths, ios::in | ios::out | ios::binary);
    while(getline(file, line)){
        if(line.empty()) continue;
        if(!isValidPathLine(line)){
            //The line is not like this:
            //a,MyDisk.mia
            results.push_back({false, "SYSTEM: Line with invalid format found in 'Paths.txt'"});
            change = true;
            continue;
        }

        //----------------------------------
        //pending implementation of the scenario in which 2 disks have the same character
        //----------------------------------

        string currentPath = Utilities::Trim(line.substr(2));
        if(!Utilities::diskExist(currentPath)){
            //in case the path is written but the disk doesn exists
            //the path is discarded
            results.push_back({false, "SYSTEM: The path [" + currentPath + "] exists in 'Paths.txt', but the disk was not found, path discarded"});
            change = true;
            continue;
        }
        counter += 1;
        newContent += line + "\n";
    }
    file.close();
    
    if(change){
        //The data is eliminated, then the new data is written
        fstream file(paths, ios::out | ios::trunc);
        file << newContent;
        file.close();
    }
    
    return results;
}

CommandResult ControllerSystem::registerPath(const std::string& path){
    //checking if the file exists(not a disk)
    string paths = "Disks/Paths.txt";
    fstream file(paths, ios::in | ios::out | ios::binary);

    bool used[52] {false};              //Array to find the first available character
    string line;
    while(getline(file, line)){
        if(line.empty()) continue;
        char character = line[0];
        if(character >= 'a' && character <= 'z') used[character - 'a'] = true;
        else if(character >= 'A' && character <= 'Z') used[character - 'A'] = true;
    }
    file.close();
    char available = '\0';
    int i = 0;
    for(i; i < 26; i++){
        if(!used[i]){
            available = 'a' + i;
            fstream file(paths, ios::app);
            file<<available<<","<<path<<"\n";
            file.close();
            return {true, "SYSTEM: Succesfully registered path"};
        }
    }
    for(i; i < 52; i++){
        if(!used[i]){
            available = 'A' + i;
            fstream file(paths, ios::app);
            file<<available<<","<<path<<"\n";
            file.close();
            return {true, "SYSTEM: Succesfully registered path"};
        }
    }
    //Response that shouldnt be reached
    return {false, "SYSTEM: The system doesnt support any more disk"};
}

