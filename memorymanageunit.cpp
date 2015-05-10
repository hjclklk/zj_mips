//
// Created by Shor on 2015/5/10.
//

#include "MemoryManageUnit.h"
#include "MipsCPU.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <iomanip>

using namespace std;

MemoryManageUnit::MemoryManageUnit(MipsCPU &cpu, int m)
{
    theCPU = &cpu;
    size=m;
    Memory = new short[size];
    memset(Memory, 0, size*2);
}

void MemoryManageUnit::load()
{
    try{
        ifstream in("./mem.bin",ios::binary);
        if(!in.is_open()) throw exception();
        for(int i=0;!in.eof();i++) {
            in.read((char*)&Memory[i],sizeof(short));	//ROM
            char tmp=(unsigned short)Memory[i]>>8;
            Memory[i]=((Memory[i]<<8)&0xff00)|((unsigned short)tmp&0x00ff);
        }
        in.close();

    }catch(exception e){
        exit(1);
    }
}

int MemoryManageUnit::lw(int adr)	//Big_Endian | Little_Endian
{
    return ((int)Memory[adr]<<16)|((int)Memory[adr+1]&0xFFFF);
}

void MemoryManageUnit::sw(int adr, int dat)
{
    Memory[adr+0]=(short)(dat>>16);
    Memory[adr+1]=(short)(dat&0xFFFF);
}

int MemoryManageUnit::lh(int adr)
{
    return Memory[adr];
}

void MemoryManageUnit::sh(int adr, int dat)
{
    Memory[adr]=(short)(dat&0xFFFF);
    if(adr>theCPU->CRTadr) theCPU->refresh=true;
}

void MemoryManageUnit::showMem()
{
    for(int i=0; i<16; i++){
        cout << "Memory["<<dec<<i<<"]="<<setw(4)<<hex<<Memory[i] << endl;
    }
}
