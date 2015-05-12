//
// Created by Shor on 2015/5/10.
//

#ifndef MIPSCPU_MEMORYMANAGEUNIT_H
#define MIPSCPU_MEMORYMANAGEUNIT_H

class MipsCPU;

class MemoryManageUnit
{
public:
    MipsCPU	* theCPU;
    short * Memory;
    int		size;

public:
    MemoryManageUnit(MipsCPU &cpu, int m);
    void load();
    int lw(int adr);	//Big_Endian | Little_Endian
    void sw(int adr, int dat);
    int lh(int adr);
    void sh(int adr, int dat);
    void showMem();
};


#endif //MIPSCPU_MEMORYMANAGEUNIT_H
