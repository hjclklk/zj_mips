//
// Created by Shor on 2015/5/10.
//

#ifndef MIPSCPU_MIPSCPU_H
#define MIPSCPU_MIPSCPU_H

class MemoryManageUnit;

class MipsCPU {
    const static int MAXIUM=0x8000;

//	byte[]	Memory=new byte[4096];


public:
    int		PC;
    int	Rgf[32];
    const static int CRTadr=0x4000; //40*26=1024=0x4000
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
