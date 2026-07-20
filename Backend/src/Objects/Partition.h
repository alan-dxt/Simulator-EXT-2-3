#ifndef PARTITION_H_INCLUDED
#define PARTITION_H_INCLUDED

#pragma pack(push, 1)
struct Partition{
    char        part_status;        //Indicates wheter the partition is mounted
    char        part_type;          //Type of partition: Primary(P) or Extended(E)
    char        part_fit;           //Type od fit: Best(B), First(F) or Worst(W)
    int         part_start;         //Byte where the partititon starts
    int         part_s;             //Size of the partition
    char        part_name[16];
    int         part_correlative;
    char        part_id[4];         //Id generated when mounting the partition
};

#pragma pack(pop)
#endif