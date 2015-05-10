#include "cpu.h"
#include "ui_cpu.h"

cpu::cpu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::cpu)
{
    ui->setupUi(this);
}

cpu::~cpu()
{
    delete ui;
}
