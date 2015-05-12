//
// Created by Shor on 2015/5/10.
//

#include "MipsCPU.h"
#include <cstring>
#include <iostream>
#include "MemoryManageUnit.h"
#include <stdexcept>

using namespace std;
MipsCPU::MipsCPU()
{
    memset(Rgf,0,32*4);
    Rgf[0]=0;	//$zero
    Rgf[29]=0x7ffc;    //$sp=0x7ffc, on top of mem
    MMU = new MemoryManageUnit( *this, MAXIUM);
    PC=0x0040;      //text(instruction part of mem) start from 0x0040

}

void MipsCPU::boot()
{
    MMU->load();	//!!ROM init
}

void MipsCPU::run(const int run_by_step=0)
{
    int	IR, op, rd, rs, rt, sft, fun, dat, adr;
    int step=1;
    
	try{
		for(;;){
	        IR=MMU->lw(PC);
            std::cout <<"IR="<<std::hex<<IR<<std::endl;
            std::cout <<"PC="<<std::hex<<PC<<std::endl;
	        PC+=2;					// 16-bit/byte
	        if(PC >= 0x1000) PC=0x0040;
	        step++;
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
                case 8:     //jrruntime_error
                    if(Rgf[rs]>=0x1000||Rgf[rs]<0x0040) throw runtime_error("JR out of range");
                    PC = Rgf[rs];
                    break;
                case 12:    //syscall
                    switch(Rgf[2]) {    //$v0
                    case 10:    //exit
                        return;
                    default:
                        exit(1);
                    }
                    break;
                case 13:    //break
                    return;
                    break;
                case 26:    //div
                    Rgf[rd]=Rgf[rs]/Rgf[rt];
                    break;
                case 27:    //div
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
                case 38:    //xor
                    Rgf[rd]=Rgf[rs]^Rgf[rt];
                    break;
                case 42:    //slt
                    //this->showRegs();
                    if(Rgf[rs]<Rgf[rt]) Rgf[rd]=1;
                    else Rgf[rd]=0;
                    break;
                default:
                    throw runtime_error("This R-type instruction is not yet supported") ;
                    return;
                }
                break;
            case 35:	//LW
                Rgf[rt]=MMU->lw(Rgf[rs]+dat);
                break;
            case 43:	//SW
                MMU->sw(Rgf[rs]+dat, Rgf[rt]);
                break;
            case 4:		//BEQ
                if(Rgf[rs]==Rgf[rt]) PC+=(dat<<1);
                break;
            case 5:     //bne
                if(Rgf[rs]!=Rgf[rt]) PC+=(dat<<1);
                break;
            case 1:     //bgez&bltz
                switch(Rgf[rt]) {
                case 0: //bltz
                    if(Rgf[rs]<0) PC+=(dat<<1);
                    break;
                case 1:
                    if(Rgf[rs]>=0) PC+=(dat<<1);
                    break;
                default:
                    throw runtime_error("OPC=1,rt!=0&&rt!=1.Not a inst");
                    break;
                }
                break;
            case 2:		//J
                PC=(PC&0xF8000000)|(adr<<1);
                break;
            case 3:     //jal
                Rgf[31]=(PC+2)>=0x1000?0x0040:PC+2;
                if((adr<<1)>=0x1000||(adr<<1)<=0x0040) throw runtime_error("Jal jump out of range");
                PC=adr<<1;
                break;
            case 6:     //blez
                if(Rgf[rs]<=0) PC+=(dat<<1);
                break;
            case 7:     //bgtz
                if(Rgf[rs]>0)  PC+=(dat<<1);
            case 8:     //addi
                Rgf[rt]=Rgf[rs]+dat;
                break;
            case 9:     //addiu
                Rgf[rt]=Rgf[rs]+((int)dat&0x0000ffff);
                break;
            case 10:    //slti
                if(Rgf[rs]<dat) Rgf[rt]=1;
                else Rgf[rt]=0;
                break;
            case 11:    //sltiu
                if(Rgf[rs]< ((int)dat&0x0000ffff) ) Rgf[rt]=1;
                else Rgf[rt]=0;
                break;
            case 12:    //andi
                Rgf[rt]=Rgf[rs]&((int)dat&0x0000ffff);
                break;
            case 13:    //ori
                Rgf[rs]=Rgf[rs]|((int)dat&0x0000ffff);
                break;
            case 15:    //lui
                Rgf[rs]=dat;
                break;
            case 32:    //lb
                throw runtime_error("The mem is 16bit/byte, 8bit/byte is not supported");
                break;
            case 33:    //lh
                Rgf[rt]=MMU->lh(Rgf[rs]+dat);
                break;
            case 36:    //lbu
                throw runtime_error("The mem is 16bit/byte, 8bit/byte is not supported");
                break;
            case 37:    //lhu
                Rgf[rt]=((int)MMU->lh(Rgf[rs]+dat)&0x0000ffff);
                break;
            case 40:    //sb
                throw runtime_error("The mem is 16bit/byte, 8bit/byte is not supported");
                break;
            case 41:    //sh
                MMU->sh(Rgf[rs]+dat,Rgf[rt]&0x0000ffff);
                break;
            default:
                throw runtime_error("This instruction is not yet supported");
                return;
	        }

            if(run_by_step) return ;
	    }//for
    } catch(runtime_error e ) {
		
	}
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
