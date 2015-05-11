#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <map>
#include <string>
#include <QMap>
#include "cpu.h"
using std::map;
using std::string;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
     const QString TypeR = "000000";
     const QString TypeJ = "00001";
     const QString EmptyFive = "00000";
     const int TypeI_num1 = 4;
     const int TypeI_num2 = 3;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QString change_10_to_2(QString str,int base1,int base2, int len);
    QString change_num_to_str(int number,int len);
    QString processAtomicBracket(QString atomicExpression);
    QString processExpression(QString str);
    QString replaceDefineStr(QString str);
    void loadFile(QString fileName);
    void loadRegisterFile(QString fileName);
    void loadTypeFile(QString fileName);
    void loadFuncFile(QString fileName);
    void loadTypeIFile(QString filename);
    void processDefine(QStringList DefineList);
    void processTypeR(QStringList sentenceList,int line);
    void processTypeJ(QStringList sentenceList,int line);
    void processTypeI_1(QStringList sentenceList,int line);
    void processTypeI_2(QStringList sentenceList,int line);
    void processTypeI_3(QStringList sentenceList,int line);
    void processMemory(QStringList MemoryList);
    void processMessageError(QString error,int line);
    void pseudoInstruction(int& line, std::vector<int>& editLine,QString &Str ,QStringList &Strlist);
    void list_to_low(QStringList &list);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
    QMap<QString, QString> mapForRegister;
    QMap<QString, QString> mapForType;
    QMap<QString, QString> mapForFunc;
    QMap<QString, QString> mapForType_I;
    QMap<QString, QString> mapForDefine;
    QMap<QString, int> mapForLabel;
    QMap<QString, int> mapForMemory;
    QString DataStr;
    int memoryStart;
    cpu *myCpuWidget;
};

#endif // MAINWINDOW_H
