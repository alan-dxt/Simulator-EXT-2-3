#ifndef COMMANDRESULT_H_INCLUDED
#define COMMANDRESULT_H_INCLUDED

#include <string>
//Response for the commands
struct CommandResult{
    bool success;
    std::string message;
};

#endif