#ifndef CPU_H
#define CPU_H

#include <QWidget>
#include <QStandardItemModel>
#include "mipscpu.h"

namespace Ui {
class cpu;
}

class cpu : public QWidget
{
    Q_OBJECT

public:
    explicit cpu(QWidget *parent = 0);
    ~cpu();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::cpu *ui;
    QStandardItemModel *registerModel;
    QStandardItemModel *memoryModel;

    MipsCPU tmpCPU;
};

#endif // CPU_H
