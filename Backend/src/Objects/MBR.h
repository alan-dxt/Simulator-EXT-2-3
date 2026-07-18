#ifndef MBR_H_INCLUDED
#define MBR_H_INCLUDED

#include "./Partition.h"
#include <ctime>

#pragma pack(push, 1)
struct MBR{
    int         mbr_size;           //Disk size in bytes
    time_t      mbr_date;           //Date of creation
    int         mbr_dsk_signatire;  //Number that identifies the disk(random)
    char        dsk_fit;            //Type of fit in the disk: Best(B), First(F) or Worst(W)
    Partition   partitions[4];
}

#pragma pack(pop)

#endif