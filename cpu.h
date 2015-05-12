#ifndef CPU_H
#define CPU_H

#include <QWidget>
#include <QStandardItemModel>
#include "mipscpu.h"
#include "memorymanageunit.h"
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
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::cpu *ui;
    MipsCPU *tmpCPU;
    QStandardItemModel *registerModel;
    QStandardItemModel *memoryModel;
    int runLine;
};

#endif // CPU_H
