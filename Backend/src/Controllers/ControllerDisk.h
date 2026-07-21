#ifndef CONTROLLERDISK_H_INCLUDED
#define CONTROLLERdISK_H_INCLUDED

#include <string>
#include "../Objects/MBR.h"
#include "../Objects/CommandResult.h"

class ControllerDisk{
    public:
        static MBR readMBR(const std::string& path);
        static void writeMBR(const std::string& path, MBR& mbr);
        static bool diskExist(const std::string& path);
        static CommandResult createDisk(const std::string& path, char& fit, int& size);
        static CommandResult deleteDisk(const std::string& path);
};

#endif