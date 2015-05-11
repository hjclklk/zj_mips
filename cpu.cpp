#include "cpu.h"
#include "ui_cpu.h"
#include "mainwindow.h"
#include <QStandardItemModel>
#include <QDebug>
extern QVector<QString> listForRegister;
cpu::cpu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::cpu)
{
    ui->setupUi(this);
    QString tempRegister;
    registerModel = new QStandardItemModel();
    int i = 0;

    //qDebug() << listForRegister[0];
    foreach (tempRegister, listForRegister){
        registerModel->setVerticalHeaderItem(i,new QStandardItem(tempRegister));
        qDebug() << tempRegister;
        i++;
    }
    int stack = 0xFFFFFFF;
    i = 0;
    this->ui->tableView->setModel(registerModel);
}

cpu::~cpu()
{
    delete ui;
}
