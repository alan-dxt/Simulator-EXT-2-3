#ifndef CONTROLLERDISK_H_INCLUDED
#define CONTROLLERDISK_H_INCLUDED

#include <string>
#include <vector>
#include "../Objects/MBR.h"
#include "../Objects/CommandResult.h"

class ControllerDisk{
    public:
        static MBR readMBR(const std::string& path);
        static void writeMBR(const std::string& path, MBR& mbr);
        static std::vector<CommandResult> createDisk(const std::string& path, char& fit, int& size);
        static std::vector<CommandResult> deleteDisk(const std::string& path);
};

#endif