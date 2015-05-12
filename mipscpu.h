//
// Created by Shor on 2015/5/10.
//

#ifndef MIPSCPU_MIPSCPU_H
#define MIPSCPU_MIPSCPU_H

class MemoryManageUnit;

class MipsCPU {
    const static int MAXIUM=0x8000; //0-0x0040 reserved, 0x0040-0x1000 text,
                                        //0x1000-0x1080 static,
                                        //0x1080-0x8000 dynamic.
//	byte[]	Memory=new byte[4096];
    int		PC;

public:
//    const static int CRTadr=0x7c00; //40*26=1024=0x400, won't be used in a simulator
//    bool	refresh=false;
    MemoryManageUnit * MMU;
    int	Rgf[32];
public:
    MipsCPU();
    ~MipsCPU();
    void boot();
    void run(const int run_by_step=0);
    void showRegs();

};


#endif //MIPSCPU_MIPSCPU_H
