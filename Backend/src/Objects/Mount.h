#ifndef MOUNT_H_INCLUDED
#define MOUNT_H_INCLUDED

#include <string>

struct Mount{
    std::string path;
    int start;
    char id[4];
    char name[15];
};


#endif