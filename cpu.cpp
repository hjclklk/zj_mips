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

    MipsCPU tmpCPU;
    //    tmpCPU.boot();
    //    tmpCPU.run();
    //    tmpCPU.showRegs();
    //    tmpCPU.MMU->showMem();
    \

    QString tempRegister;
    QString registerTempData,temp,memoryrTempData;
    registerModel = new QStandardItemModel();
    memoryModel = new QStandardItemModel();
    //qDebug() << listForRegister[0];
    int i = 0;
    foreach (tempRegister, registerList){
        registerModel->setVerticalHeaderItem(i,new QStandardItem(tempRegister));
        registerModel->setItem(i,0,new QStandardItem(registerTempData.setNum(tmpCPU.Rgf[i],16)));
        qDebug() << tmpCPU.Rgf[i] << i;
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

cpu::~cpu()
{
    delete ui;
}
