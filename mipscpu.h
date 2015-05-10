//
// Created by Shor on 2015/5/10.
//

#ifndef MIPSCPU_MIPSCPU_H
#define MIPSCPU_MIPSCPU_H

class MemoryManageUnit;

class MipsCPU {
    const static int MAXIUM=0x8000;
    int	Rgf[32];
//	byte[]	Memory=new byte[4096];
    int		PC;

public:
    const static int CRTadr=0x6000;
    bool	refresh=false;
    MemoryManageUnit * MMU;
public:
    MipsCPU();
    void boot();
    void run();
    void showRegs();

};


#endif //MIPSCPU_MIPSCPU_H
