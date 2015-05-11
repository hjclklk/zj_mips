//
// Created by Shor on 2015/5/10.
//

#ifndef MIPSCPU_MIPSCPU_H
#define MIPSCPU_MIPSCPU_H

class MemoryManageUnit;

class MipsCPU {
    const static int MAXIUM=0x80000000;
    int	Rgf[32];
//	byte[]	Memory=new byte[4096];
    int		PC;

public:
//    const static int CRTadr=0x7c00; //40*26=1024=0x400, won't be used in a simulator
    bool	refresh=false;
    MemoryManageUnit * MMU;
public:
    MipsCPU();
    ~MipsCPU();
    void boot();
    void run();
    void showRegs();

};


#endif //MIPSCPU_MIPSCPU_H
