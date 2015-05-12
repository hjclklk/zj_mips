#include "binary.h"
#include <iostream>
#include <string>
#include <bitset>
#include <QTextStream>

using namespace std;

QMap<QString, QString> Binary::registers;
QMap<QString, int> Binary::opTypes;
QMap<int, int> Binary::labels;
QMap<QString, QString> Binary::RTypes;
QMap<QString, QString> Binary::ITypes;
QMap<QString, QString> Binary::JTypes;
QMap<QString, QString> Binary::opCode;
QMap<QString, QString> Binary::functCode;

int Binary::def = 0;

void Binary::init()
{
    if (!def)
    {
        registers.clear();
        registers["00000"]    = "$zero";
        registers["00001"]    = "$at";
        registers["00010"]    = "$v0";
        registers["00011"]    = "$v1";
        registers["00100"]    = "$a0";
        registers["00101"]    = "$a1";
        registers["00110"]    = "$a2";
        registers["00111"]    = "$a3";
        registers["01000"]    = "$t0";
        registers["01001"]    = "$t1";
        registers["01010"]    = "$t2";
        registers["01011"]    = "$t3";
        registers["01100"]    = "$t4";
        registers["01101"]    = "$t5";
        registers["01110"]    = "$t6";
        registers["01111"]    = "$t7";
        registers["10000"]    = "$s0";
        registers["10001"]    = "$s1";
        registers["10010"]    = "$s2";
        registers["10011"]    = "$s3";
        registers["10100"]    = "$s4";
        registers["10101"]    = "$s5";
        registers["10110"]    = "$s6";
        registers["10111"]    = "$s7";
        registers["11000"]    = "$t8";
        registers["11001"]    = "$t9";
        registers["11010"]    = "$k0";
        registers["11011"]    = "$k1";
        registers["11100"]    = "$gp";
        registers["11101"]    = "$sp";
        registers["11110"]    = "$fp";
        registers["11111"]    = "$ra";

        opTypes.clear();
        opTypes["000000"]  = 'R';
        opTypes["100011"]   = 'I';
        opTypes["101011"]   = 'I';
        opTypes["001000"]  = 'I';
        opTypes["000010"]    = 'J';
        opTypes["000011"]  = 'J';
        opTypes["001001"]  = 'I';
        opTypes["001100"]  = 'I';
        opTypes["001101"]  = 'I';
        opTypes["001110"]  = 'I';
        opTypes["001010"]  = 'I';
        opTypes["001011"]  = 'I';
        opTypes["000100"]  = 'I';
        opTypes["000101"]  = 'I';

        RTypes["100000"] = "R1";
        functCode["100000"] = "add";

        RTypes["100001"] = "R1";
        functCode["100001"] = "addu";

        RTypes["100010"] = "R1";
        functCode["100010"] = "sub";

        ITypes["100011"] = "I1";
        opCode["100011"] = "lw";

        ITypes["101011"] = "I1";
        opCode["101011"] = "sw";

        ITypes["001000"] = "I2";
        opCode["001000"] = "addi";

        ITypes["001001"] = "I2";
        opCode["001001"] = "addiu";

        ITypes["001100"] = "I2";
        opCode["001100"] = "andi";

        ITypes["001101"] = "I2";
        opCode["001101"] = "ori";

        ITypes["001110"] = "I2";
        opCode["001110"] = "xori";

        JTypes["000010"] = "J1";
        opCode["000010"] = "j";

        JTypes["000011"] = "J1";
        opCode["000011"] = "jal";

        RTypes["001000"] = "R2";
        functCode["001000"] = "jr";

        RTypes["100100"] = "R1";
        functCode["100100"] = "and";

        RTypes["100101"] = "R1";
        functCode["100101"] = "or";

        RTypes["100111"] = "R1";
        functCode["100111"] = "nor";

        RTypes["100110"] = "R1";
        functCode["100110"] = "xor";

        RTypes["101010"] = "R1";
        functCode["101010"] = "slt";

        RTypes["101011"] = "R1";
        functCode["101011"] = "sltu";

        ITypes["001010"] = "I2";
        opCode["001010"] = "slti";

        ITypes["001011"] = "I2";
        opCode["001011"] = "sltiu";

        ITypes["000100"] = "I2";
        opCode["000100"] = "beq";

        ITypes["000101"] = "I2";
        opCode["000101"] = "bne";

        labels.clear();
        def = 1;
    }
}

Binary::Binary()
{

}

Binary::~Binary()
{

}

QString Binary::R_type(QString code)
{
    QString instruction = code.mid(26, 6);

    QString op = functCode[instruction],
            rs = registers[code.mid(6, 5)],
            rt = registers[code.mid(11, 5)],
            rd = registers[code.mid(16, 5)];

    //QTextStream cout(stdout, QIODevice::WriteOnly);

    //cout << code.mid(6, 5) << registers[code.mid(6, 5)] << rs <<endl;

    int shamt = registers[code.mid(21, 5)].toInt(NULL, 2),
        funct = code.mid(26, 6).toInt(NULL, 2);

    if (RTypes[instruction] == "R1") {
        return op + ' ' + rd + ", " + rs + ", " + rt;
    }

    if (RTypes[instruction] == "R2") {
        return op + ' ' + rs;
    }

    return NULL;
}

QString Binary::I_type(QString code)
{
    QString instruction = code.left(6);

    QString op = opCode[instruction],
            rs = registers[code.mid(6, 5)],
            rt = registers[code.mid(11, 5)];

    int constant = code.mid(16, 16).toInt(NULL, 2);

    if (ITypes[instruction] == "I1") {
        return op + ' ' + rt + ", " + QString::number(constant) + '(' + rs + ')';
    }

    if (ITypes[instruction] == "I2") {
        return op + ' ' + rt + ", " + rs + ", " + QString::number(constant);
    }

    return NULL;
}

QString Binary::J_type(QString code)
{
    QString instruction = code.left(6);

    QString op = opCode[instruction],
            target = QString::number(code.mid(6, 26).toInt(NULL, 2));

    if (JTypes[instruction] == "J1") {
        return op + ' ' + target;
    }

    return op + target;
}


QString Binary::binaryToMips(QString binaryCode)
{
    init();
    //QTextStream cout(stdout, QIODevice::WriteOnly);
    QStringList code = binaryCode.toUpper().split('\n');
    QString mips = "";

    for (int i = 0; i < code.size(); i++)
    {
        QString instruction = code[i].left(6);

        if (opTypes[instruction] == 'J')
        {
            int addr = code[i].right(26).toInt(NULL, 2);
            labels[addr] = addr;
        }
    }

    int addr = 0x00100000;

    for (int i = 0; i < code.size(); i++)
    {
        QString instruction = code[i].left(6);

        QMap<QString, int>::const_iterator t = opTypes.find(instruction);
        if (t != opTypes.end() && t.key() == instruction) {
           if (labels[addr] == addr) {
               mips += QString::number(addr) + ":\n";
           }
           addr += 1;
           switch (t.value()) {
           case 'R':
               mips += R_type(code[i]) + '\n';
               break;

           case 'I':
               mips += I_type(code[i]) + '\n';
               break;

           case 'J':
               mips += J_type(code[i]) + '\n';
               break;

           default:
               break;
           }
        }
    }

    return mips;
}

