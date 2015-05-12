#include "cpu.h"
#include "ui_cpu.h"
#include <QDebug>


cpu::cpu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::cpu)
{
    ui->setupUi(this);

    myMipsCPU = new MipsCPU();
    myMipsCPU->boot();

    QString tempRegister;
    QString registerTempData,temp,memoryrTempData;
    registerModel = new QStandardItemModel();
    memoryModel = new QStandardItemModel();
    //qDebug() << listForRegister[0];
    int i = 0;
    foreach (tempRegister, registerList){
        registerModel->setVerticalHeaderItem(i,new QStandardItem(tempRegister));
        registerModel->setItem(i,0,new QStandardItem(registerTempData.setNum(myMipsCPU->Rgf[i],16)));

        i++;
    }
    int stack = 0x00000000;
    i = 0;
    while (i < 0xFFFF){
        temp = QString("%1").arg(stack,8,16);
        temp = temp.replace(" ","0");
        memoryModel->setVerticalHeaderItem(i,new QStandardItem(temp));
        temp = QString("%1").arg((unsigned short)(myMipsCPU->MMU->Memory[i]),4,16);
//        qDebug() <<short(myMipsCPU->MMU->Memory[i]);
        temp = temp.replace(" ","0");
        memoryModel->setItem(i,0,new QStandardItem(temp));
        stack += 1;
        i++;

    }
    this->ui->tableView->setModel(registerModel);
    this->ui->tableView_2->setModel(memoryModel);

    //    tmpCPU.run();
    //    tmpCPU.showRegs();
    //    tmpCPU.MMU->showMem();
    \

}

cpu::~cpu()
{
    delete ui;
}

void cpu::on_pushButton_clicked()
{

}
