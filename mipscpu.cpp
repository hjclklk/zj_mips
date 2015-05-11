//
// Created by Shor on 2015/5/10.
//

#include "MipsCPU.h"
#include <cstring>
#include <iostream>
#include "MemoryManageUnit.h"

MipsCPU::MipsCPU()
{
    memset(Rgf,0,32*4);
    Rgf[0]=0;	//$zero
    Rgf[29]=0x2000;    //$sp=0x2000
    MMU = new MemoryManageUnit( *this, MAXIUM);
    PC=0;
}

void MipsCPU::boot()
{
    MMU->load();	//ROM init
}

void MipsCPU::run()
{
    int	IR, op, rd, rs, rt, sft, fun, dat, adr;
    int step=1;
    for(;;){
        IR=MMU->lw(PC);
        std::cout <<"IR="<<std::hex<<IR<<std::endl;
        PC+=2;					//16-bit/byte
        if(PC > MAXIUM) PC%=MAXIUM;
        step++;
//add $s1,$s2,$s3 = 0000 0010 0111 0001 1001 0000 0010 0000
                     //0x02719020
//R:	op:6,rs:5,rt:5,rd:5,sft:5,fun:6
//I:	op:6,$rs:5,$rt:5,dat:16
//J:	op:6,adr:26
        op=(IR>>26)&63;
        rs=(IR>>21)&31;
        rt=(IR>>16)&31;
        rd=(IR>>11)&31;
        sft=(IR>>6)&31;
        fun=IR&63;
        dat=(int)(short)(IR&0xFFFF);
        adr=IR&0x3FFFFFF;
        switch(op){
            case 0:		//R-type
                switch(fun){
//                        case 9:     //jalr
//                        case 13:    //break
                    //!!
//                            break;
                    case 26:    //div
                        Rgf[rd]=Rgf[rs]/Rgf[rt];
                        break;
                    case 27:
                        Rgf[rd]=(unsigned int)Rgf[rs]/(unsigned int)Rgf[rt];
                        break;
                    case 32:	//ADD
                        Rgf[rd]=Rgf[rs]+Rgf[rt];
                        break;
                    case 33:    //addu
                        Rgf[rd]=((unsigned int)Rgf[rs]+(unsigned int)Rgf[rt]);
                        break;
                    case 34:	//SUB
                        Rgf[rd]=Rgf[rs]-Rgf[rt];
                        break;
                    case 35:    //subu
                        Rgf[rd]=(unsigned int)Rgf[rs]-(unsigned int)Rgf[rt];
                        break;
                    case 36:    //and
                        Rgf[rd]=Rgf[rs]&Rgf[rt];
                        break;

                    case 42:    //slt
                        this->showRegs();
                        if(Rgf[rs]<Rgf[rt]) Rgf[rd]=1;
                        else Rgf[rd]=0;
                        break;
                    default:
                        std::cout << "Error" << std::endl;
                        return;
                }
                break;
            case 43:	//LW
                Rgf[rt]=MMU->lw(Rgf[rs]+dat);
                break;
            case 37:	//SW
                MMU->sw(Rgf[rs]+dat, Rgf[rt]);
                break;
            case 4:		//BEQ
//                    this->showRegs();
                if(Rgf[rs]==Rgf[rt]) PC+=(dat<<1);
                break;
            case 5:
                if(Rgf[rs]!=Rgf[rt]) PC+=(dat<<1);
                break;
            case 2:		//J
                PC=(PC&0xF8000000)|(adr<<1);
                break;
            case 8:     //addi
                Rgf[rt]=Rgf[rs]+dat;
                break;
            default:
                std::cout << "Error" << std::endl;
                return;
        }

        if(refresh){	//VM refresh
            for(int i=0; i<40*26; i++){
                std::cout << (char)MMU->lh(i+CRTadr) << std::endl;
//				ZBHZ.draw(i%40,i/40,MMU.lh(i+CRTadr));
            }	refresh=false;
        }
    }//for
}

void MipsCPU::showRegs()
{
    for (int i=0; i<32; i++) {
        std::cout << "Reg[" <<std::dec<< i << "]=" << std::dec<<Rgf[i] << std::endl;
    }
}

MipsCPU::~MipsCPU()
{
    delete MMU;
}
