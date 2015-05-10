#ifndef CPU_H
#define CPU_H

#include <QWidget>

namespace Ui {
class cpu;
}

class cpu : public QWidget
{
    Q_OBJECT

public:
    explicit cpu(QWidget *parent = 0);
    ~cpu();

private:
    Ui::cpu *ui;
};

#endif // CPU_H
