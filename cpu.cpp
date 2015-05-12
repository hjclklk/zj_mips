#include "cpu.h"
#include "ui_cpu.h"
#include <QDebug>
#include "mipscpu.h"
#include "memorymanageunit.h"

extern QVector<QString> registerList;

cpu::cpu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::cpu)
{
    ui->setupUi(this);

    tmpCPU = new MipsCPU;
    tmpCPU->boot();
    //    tmpCPU.showRegs();
    //    tmpCPU.MMU->showMem();


    QString tempRegister;
    QString registerTempData,temp;
    registerModel = new QStandardItemModel();
    memoryModel = new QStandardItemModel();
    //qDebug() << listForRegister[0];
    int i = 0;
    foreach (tempRegister, registerList){
        registerModel->setVerticalHeaderItem(i,new QStandardItem(tempRegister));
        registerModel->setItem(i,0,new QStandardItem(registerTempData.setNum(tmpCPU->Rgf[i],16)));
        qDebug() << tmpCPU->Rgf[i] << i;
        i++;
    }
    int stack = 0x00000000;
    i = 0;
    while (i < 0xFFFF){
        temp = QString("%1").arg(stack,8,16);
        temp = temp.replace(" ","0");
        memoryModel->setVerticalHeaderItem(i,new QStandardItem(temp));
        temp = QString("%1").arg((unsigned short)(tmpCPU->MMU->Memory[i]),4,16);
        temp = temp.replace(" ","0");
        memoryModel->setItem(i,0,new QStandardItem(temp));
        stack += 1;
        i++;
    }
    this->ui->tableView->setModel(registerModel);
    this->ui->tableView_2->setModel(memoryModel);

    for (int i = 0x0040;i<tmpCPU->MMU->Size;i+=2){
        this->ui->textBrowser->append(QString("Line%1 : %2").arg(QString::number((i-0x0040)/2+1),QString::number(tmpCPU->MMU->lw(i),16)));
        this->ui->textBrowser->append("\n");
    }
    runLine = 0; //for end or start
    this->ui->label_2->setText(QString::number(runLine));
}

cpu::~cpu()
{
    delete ui;
}

void cpu::on_pushButton_2_clicked()
{
    tmpCPU.boot();
    tmpCPU.run();
    QString tempRegister;
    QString registerTempData,temp,memoryrTempData;
    registerModel = new QStandardItemModel();
    memoryModel = new QStandardItemModel();
    //qDebug() << listForRegister[0];
    int i = 0;
    foreach (tempRegister, registerList){
        registerModel->setVerticalHeaderItem(i,new QStandardItem(tempRegister));
        registerModel->setItem(i,0,new QStandardItem(registerTempData.setNum(tmpCPU.Rgf[i],16)));
//        qDebug() << tmpCPU.Rgf[i] << i;
        i++;
    }
    int stack = 0x00002000;
    i = 0;
    while (i < 1000){
        temp = QString("%1").arg(stack,8,16);
        temp = temp.replace(" ","0");
        memoryModel->setVerticalHeaderItem(i,new QStandardItem(temp));
        temp = QString("%1").arg(tmpCPU.MMU->Memory[i],4,16);
        temp = temp.replace(" ","0");
        memoryModel->setItem(i,0,new QStandardItem(temp));
        stack += 1;
        i++;

    }
    this->ui->tableView->setModel(registerModel);
    this->ui->tableView_2->setModel(memoryModel);
}

void cpu::on_pushButton_clicked()
{
    tmpCPU->run(1);
    runLine = (tmpCPU->PC - 0x0040) / 2;
    this->ui->label_2->setText(QString::number(runLine));
    QString tempRegister;
    QString registerTempData,temp;
    int i = 0;
    foreach (tempRegister, registerList){
        registerModel->setItem(i,0,new QStandardItem(registerTempData.setNum(tmpCPU->Rgf[i],16)));
//        qDebug() << tmpCPU->Rgf[i] << i;
        i++;
    }
    int stack = 0x00000000;
    i = 0;
    while (i < 0xFFFF){
        temp = QString("%1").arg((unsigned short)(tmpCPU->MMU->Memory[i]),4,16);
        temp = temp.replace(" ","0");
        memoryModel->setItem(i,0,new QStandardItem(temp));
        stack += 1;
        i++;
    }
}

void cpu::on_pushButton_2_clicked()
{
    tmpCPU->run(0);
    runLine = 0; //for end or start
    this->ui->label_2->setText(QString::number(runLine));
    QString tempRegister;
    QString registerTempData,temp;
    int i = 0;
    foreach (tempRegister, registerList){
        registerModel->setItem(i,0,new QStandardItem(registerTempData.setNum(tmpCPU->Rgf[i],16)));
        //qDebug() << tmpCPU->Rgf[i] << i;
        i++;
    }
    int stack = 0x00000000;
    i = 0;
    while (i < 0xFFFF){
        temp = QString("%1").arg((unsigned short)(tmpCPU->MMU->Memory[i]),4,16);
        temp = temp.replace(" ","0");
        memoryModel->setItem(i,0,new QStandardItem(temp));
        stack += 1;
        i++;
    }
}

