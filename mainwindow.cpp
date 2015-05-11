#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QStringList>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <vector>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QDataStream>
#include <stdio.h>
#include <string>
#include "mipscpu.h"
#include "memorymanageunit.h"
#include "cpu.h"
QVector<QString> listForRegister;
//using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //QString filename("d:\config2.txt");
    loadFile(QString("./config2.txt"));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::loadFile(QString fileName)
{
    /*QFile file(fileName);
    if (!file.open(QIODevice:: ReadOnly | QIODevice::Text))
    {
        QMessageBox::information(this,"error","can't open file");
        return;
    }

    QTextStream textStream(&file);
    QString textLine;
    QStringList textLineList;
    QString text;
    //int count = 0;
    while (!textStream.atEnd())
    {
        textLine = textStream.readLine();
        textLineList = textLine.split(QRegExp("\\s+"),QString::SkipEmptyParts);
        text = text+"\n" + textLineList.at(0) + " " + textLineList.at(textLineList.size()-1);
        qDebug() << textLineList;
        //qDebug() << textStream.readAll();
        //if (count == 10) break;
        //count++;
    }
    //qDebug() << count;
    file.close();
    QFile fileout("./1.txt");
    if (!fileout.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::information(this,"error","can't open file");
        return;
    }
    QTextStream out(&fileout);
    out << text;
    //qDebug() << text;
    fileout.close();*/
//    qDebug() << QDir::currentPath() << endl;
    loadRegisterFile(QString("./register.txt"));
    loadTypeFile(QString("./type.txt"));
    loadFuncFile(QString("./function.txt"));
    loadTypeIFile(QString("./typeI.txt"));
}

void MainWindow::loadTypeIFile(QString fileName)
{
    QString textLine;
    QStringList textLineList;

    QFile file(fileName);
//    qDebug() << QDir::currentPath() << endl;
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::information(this,"error","can't open file");
        return;
    }

    QTextStream textStream1(&file);
    while (!textStream1.atEnd())
    {
        textLine = textStream1.readLine();
        textLineList = textLine.split(QRegExp("\\s+"),QString::SkipEmptyParts);
        mapForType_I.insert(textLineList[0].toLower(),textLineList[1]);
        //qDebug() << textLine;
    }
    file.close();
}

void MainWindow::loadRegisterFile(QString fileName)
{
    QString textLine;
    QStringList textLineList;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::information(this,"error","can't open file");
        return;
    }

    QTextStream textStream1(&file);

    //QString text;
    //int count = 0;
    while (!textStream1.atEnd())
    {
        textLine = textStream1.readLine();
        textLineList = textLine.split(QRegExp("\\s+"),QString::SkipEmptyParts);
        mapForRegister.insert(textLineList[0].toLower(),textLineList[1].toLower());
        listForRegister.push_back(textLineList[0].toLower());
        //qDebug() << textLine;
    }
    file.close();
}

void MainWindow::loadTypeFile(QString fileName)
{
    QString textLine;
    QStringList textLineList;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::information(this,"error","can't open file");
        return;
    }

    QTextStream textStream1(&file);

    //QString text;
    //int count = 0;
    while (!textStream1.atEnd())
    {
        textLine = textStream1.readLine();
        textLineList = textLine.split(QRegExp("\\s+"),QString::SkipEmptyParts);
        mapForType.insert(textLineList[0].toLower(),textLineList[1].toLower());
        //qDebug() << textLine;
    }
    //qDebug() << mapForType.take("sub");
    file.close();
}

void MainWindow::loadFuncFile(QString fileName)
{
    QString textLine;
    QStringList textLineList;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::information(this,"error","can't open file");
        return;
    }

    QTextStream textStream1(&file);

    //QString text;
    //int count = 0;
    while (!textStream1.atEnd())
    {
        textLine = textStream1.readLine();
        textLineList = textLine.split(QRegExp("\\s+"),QString::SkipEmptyParts);
        mapForFunc.insert(textLineList[0].toLower(),textLineList[1].toLower());
        //qDebug() << textLine;
    }
    //qDebug() << mapForFunc.take("sub");
    file.close();
}

void MainWindow::on_pushButton_clicked()
{
    //assemble code
    ui->textBrowser->clear();
    QString assembleCode,sentence;
    QStringList assembleCodeListEdit,assembleCodeList,sentenceList,DefineList;
    QMap<QString,QString>::iterator typeIter;

    std::vector<int> editLine;
    assembleCode = ui->plainTextEdit->toPlainText();
    assembleCodeListEdit = assembleCode.split("\n");
    //qDebug() << assembleCodePerSentence.length();
    int line = 0; //recorder line when assemble
    memoryStart = 0x1000;   //0x10000000 would be too large.
    mapForMemory.clear();
    mapForLabel.clear();
    mapForDefine.clear();
    // new file and empty file
    QFile file("./data");
    file.open(QIODevice::WriteOnly);
    file.close();
    file.open(QIODevice::WriteOnly | QIODevice::Truncate);
    QDataStream out(&file);
    out << qint8(01);   //!!why? 求注释...
    file.close();
    try{

        editLine.push_back(0);
        foreach (sentence,assembleCodeListEdit) //!!What does this foreach do? 格式指令和伪指令？
        {
            QString Str = sentence;
            DefineList = sentence.simplified().split(QRegExp("\\s+"),QString::SkipEmptyParts);
            if (Str.simplified() == "") continue;
            int indexOfLabel = sentence.lastIndexOf(":");
            if (indexOfLabel == -1){    //格式指令或者标签

            }
            else{
               QString labelStr = sentence;
               labelStr.remove(indexOfLabel,labelStr.size()-indexOfLabel);
               if (mapForLabel.count(labelStr) != 0) throw QString("'%1': this label is used before").arg(labelStr);
               mapForLabel.insert(labelStr,line+1);
               Str = Str.remove(0,indexOfLabel+1).simplified();
               //qDebug() << Str;
               if (Str != ""){

               }
               else
                   continue;
            }
            if (DefineList[0] == "MOVE"){// 伪指令
                if (DefineList.size() != 3) throw QString("don't match MOVE instruction");
                if (mapForRegister.count(DefineList[1]) == 0) throw QString("%1 don't match any register").arg(DefineList[1]);
                if (mapForRegister.count(DefineList[2]) == 0) throw QString("%1 don't match any register").arg(DefineList[2]);
                assembleCodeList.append("add , "+DefineList[1]+" , "+DefineList[2]+" , $zero");
                line++;
                editLine.push_back(editLine[line-1]+1);
                continue;
            }
            if (DefineList[0] == "BLT"){
                if (DefineList.size() != 4) throw QString("don't match MOVE instruction");
                assembleCodeList.append("slt ,  $at , "+DefineList[1]+" , "+DefineList[2]);
                assembleCodeList.append("bne ,  $at , $zero , "+DefineList[3]);
                line++;
                editLine.push_back(editLine[line-1]+1);
                line++;
                editLine.push_back(editLine[line-1]);
                continue;
            }
            if (DefineList[0] == "BGT"){
                if (DefineList.size() != 4) throw QString("don't match MOVE instruction");
                assembleCodeList.append("slt ,  $at , "+DefineList[2]+" , "+DefineList[1]);
                assembleCodeList.append("bne ,  $at , $zero , "+DefineList[3]);
                line++;
                editLine.push_back(editLine[line-1]+1);
                line++;
                editLine.push_back(editLine[line-1]);
                continue;
            }
            if (DefineList[0] == "BLE"){
                if (DefineList.size() != 4) throw QString("don't match MOVE instruction");
                assembleCodeList.append("slt ,  $at , "+DefineList[2]+" , "+DefineList[1]);
                assembleCodeList.append("beq ,  $at , $zero , "+DefineList[3]);
                line++;
                editLine.push_back(editLine[line-1]+1);
                line++;
                editLine.push_back(editLine[line-1]);
                continue;
            }
            if (DefineList[0] == "BGE"){
                if (DefineList.size() != 4) throw QString("don't match MOVE instruction");
                assembleCodeList.append("slt ,  $at , "+DefineList[1]+" , "+DefineList[2]);
                assembleCodeList.append("beq ,  $at , $zero , "+DefineList[3]);
                line++;
                editLine.push_back(editLine[line-1]+1);
                line++;
                editLine.push_back(editLine[line-1]);
                continue;
            }
            if (DefineList[0] == "ABS"){
                if (DefineList.size() != 3) throw QString("don't match MOVE instruction");
                assembleCodeList.append("sra ,  $at , "+DefineList[2]+" , 31");
                assembleCodeList.append("xor , "+DefineList[1]+" , "+DefineList[2]+" , $at");
                assembleCodeList.append("sub , "+DefineList[1]+" , "+DefineList[2]+" , $at");
                line++;
                editLine.push_back(editLine[line-1]+1);
                line++;
                editLine.push_back(editLine[line-1]);
                continue;
            }
            if (DefineList.size() == 3 && DefineList[1] == "equ"){
               processDefine(DefineList);
               continue;
            }else if (DefineList.size() == 3 && DefineList[1].indexOf(QRegExp(".[\\d]?byte")) != -1){   //!!我记得格式指令的变量名后面也跟着“：”
               processMemory(DefineList);
               continue;
            }
            pseudoInstruction(line,editLine,Str,assembleCodeList);
        }
//        qDebug() << line;
//        qDebug() << assembleCodeList.size();
//        foreach (sentence,assembleCodeList)
//            qDebug() << sentence;
        line = 0; //recorder line when assemble
        foreach (sentence,assembleCodeList)//!! 这边是正常的mips指令
        {
            line++;
            sentenceList = sentence.simplified().split(QRegExp("\\s*,\\s*"),QString::SkipEmptyParts);
//            qDebug() << sentenceList.size();
            if (sentenceList.empty()) continue;
            //list_to_low(sentenceList);
            //sentence is precessing at present
            if (mapForType.find(sentenceList[0]) != mapForType.end())
            {
                typeIter = mapForType.find(sentenceList[0]);
                QString checkJStr = *typeIter;
                checkJStr.remove(5,1);
                if (*typeIter == TypeR)
                {
                    processTypeR(sentenceList,line);
//                    qDebug() << sentenceList;
//                    qDebug() << *typeIter;
                }
                else if (checkJStr == TypeJ)
                {
                    processTypeJ(sentenceList,line);
                }
                else if (mapForType_I.count(sentenceList[0]) != 0)//typeI process
                {
                    if (mapForType_I.value(sentenceList[0]) == "1") //like addi
                        processTypeI_1(sentenceList,line);
                    else if (mapForType_I.value(sentenceList[0]) == "2") //like beq
                        processTypeI_2(sentenceList,line);
                    else if (mapForType_I.value(sentenceList[0]) == "3") //like lw
                        processTypeI_3(sentenceList,line);
                    else if (mapForType_I.value(sentenceList[0]) == "5") //lui $reg, immediate
                        processTypeI_5(sentenceList,line);
                }
            }
            else
                throw QString("'%1' don't match any mips instruction").arg(sentence[0]);
        }
    }
    catch (QString& error)
    {
        processMessageError(error,editLine[line]);
    }
}

QString MainWindow::replaceDefineStr(QString str)
{
    QString defineLabel;
    foreach(defineLabel, mapForDefine.keys())
    {
        str.replace(defineLabel,mapForDefine.value(defineLabel));
//        qDebug() << defineLabel << ' ' << mapForDefine.value(defineLabel);
    }
    return str;
}

void MainWindow::processDefine(QStringList DefineList)
{
    if (DefineList.size() != 3) throw QString("this don't macth fommatting size of define");
    QString expressionStr = replaceDefineStr(DefineList[2]);
    expressionStr = processExpression(expressionStr);
    QString temp = change_10_to_2(expressionStr,10,10,0);
    if (mapForDefine.count(DefineList[0]) != 0) throw QString("'%1' is used before").arg(DefineList[0]);
    mapForDefine.insert(DefineList[0],temp);
}

void MainWindow::processMemory(QStringList MemoryList)
{
    // 5,6 "abcdefg",'a'
    mapForMemory.insert(MemoryList[0],memoryStart);
    bool ok;
    QFile file("./data");
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);
    QStringList dataForMemory = MemoryList[2].split(QRegExp("\\s*,\\s*"),QString::SkipEmptyParts);
    int width = (MemoryList[1][1] == 'b')? 1 : (MemoryList[1].toStdString()[1] - '0');
    if (width == 1){
        foreach(QString tempData,dataForMemory){
            int temp = tempData.toInt(&ok);
            if (ok){    // integer byte
                out << qint8(temp);
                memoryStart += 1;
                qDebug() << temp;
            }else if (tempData.size() == 3 && tempData[0] == '\'' && tempData[2] == '\''){  //char byte
                QChar tempc = tempData[1];
                out << qint8(tempc.toLatin1());
                memoryStart += 1;
            }else if (tempData[0] == '"' && tempData[tempData.size()-1] == '"'){    //string byte???
                for (int i = 1; i < tempData.size()-1; ++i){
                    QChar tempc = tempData[i];
                    out << qint8(tempc.toLatin1());
                    memoryStart += 1;
                }
            }else{
                file.close();
                throw QString("It does not fit the formatting of memory setting");
            }
        }
    }
    else {
        file.close();
        throw QString("We now don't support '%1'").arg(MemoryList[1]);
    }
    file.close();
}

void MainWindow::pseudoInstruction(int& line, std::vector<int>& editLine,QString &Str ,QStringList &Strlist)
{
    line++;
    editLine.push_back(editLine[line-1] + 1);
    Strlist.append(Str);
}

void MainWindow::list_to_low(QStringList &list)
{
    for (int i = 0; i < list.size(); i++)
        list[i] = list[i].toLower();
}

void MainWindow::processTypeR(QStringList sentenceList,int line)
{   //!!发现不支持所有长度不为4的
//        qDebug() << sentenceList << endl;
    if (sentenceList.size() != 4 && sentenceList[0]!="syscall" ) throw QString("This line don't match numbers of R function");//!! 这边R类型不一定是3个参数的...比如syscall
    ui->textBrowser->insertPlainText(TypeR);
    if (sentenceList.size() == 1 ) { //!! 这里仅是测试用，可能需要改一下
        ui->textBrowser->insertPlainText(EmptyFive);
        ui->textBrowser->insertPlainText(EmptyFive);
        ui->textBrowser->insertPlainText(EmptyFive);
        ui->textBrowser->insertPlainText(EmptyFive);
        ui->textBrowser->insertPlainText(mapForFunc.value("syscall"));
        ui->textBrowser->insertPlainText("\n");
        return;
    }
    if (mapForRegister.count(sentenceList[3]) == 0) throw QString("%1 don't match any register").arg(sentenceList[3]);
    if (mapForRegister.count(sentenceList[1]) == 0) throw QString("%1 don't match any register").arg(sentenceList[1]);
    if (mapForRegister.count(sentenceList[2]) == 0) throw QString("%1 don't match any register").arg(sentenceList[2]);
    if (mapForFunc.count(sentenceList[0]) == 0) throw QString("%1 don't match any function").arg(sentenceList[0]);
//    qDebug() << sentenceList << endl;
    ui->textBrowser->insertPlainText(mapForRegister.value(sentenceList[3]));
    ui->textBrowser->insertPlainText(mapForRegister.value(sentenceList[1]));
    ui->textBrowser->insertPlainText(mapForRegister.value(sentenceList[2]));
    ui->textBrowser->insertPlainText(EmptyFive);
    ui->textBrowser->insertPlainText(mapForFunc.value(sentenceList[0]));
    ui->textBrowser->insertPlainText("\n");

}

void MainWindow::processTypeJ(QStringList sentenceList,int line)
{
    if (sentenceList.size() != 2) throw QString("This line don't match numbers of I function");
    if (mapForLabel.count(sentenceList[1]) == 0) throw QString("%1 don't match any Label").arg(sentenceList[1]);
    ui->textBrowser->insertPlainText(mapForType.value(sentenceList[0]));
    //ui->textBrowser->insertPlainText(sentenceList[0]);
    QString str;
    str = change_num_to_str(0x100000+mapForLabel.value(sentenceList[1])-1,26);
//    ui->textBrowser->insertPlainText(":");
    ui->textBrowser->insertPlainText(str);
    ui->textBrowser->insertPlainText("\n");
}

void MainWindow::processTypeI_1(QStringList sentenceList,int line)
{
    if (sentenceList.size() != 4) throw QString("This line don't match numbers of I function");
    if (mapForRegister.count(sentenceList[1]) == 0) throw QString("%1 don't match any register").arg(sentenceList[1]);
    if (mapForRegister.count(sentenceList[2]) == 0) throw QString("%1 don't match any register").arg(sentenceList[2]);
    ui->textBrowser->insertPlainText(mapForType.value(sentenceList[0]));
    ui->textBrowser->insertPlainText(mapForRegister.value(sentenceList[2]));
    ui->textBrowser->insertPlainText(mapForRegister.value(sentenceList[1]));
    QString str = replaceDefineStr(sentenceList[3]);
    //qDebug() << str;
    str = processExpression(str);
    str = change_10_to_2(str,10,2,16);
//    ui->textBrowser->insertPlainText(":");
    ui->textBrowser->insertPlainText(str);
    ui->textBrowser->insertPlainText("\n");
}

void MainWindow::processTypeI_2(QStringList sentenceList, int line)
{
    if (sentenceList.size() != 4) throw QString("This line don't match numbers of I function");
    if (mapForRegister.count(sentenceList[1]) == 0) throw QString("%1 don't match any register").arg(sentenceList[1]);
    if (mapForRegister.count(sentenceList[2]) == 0) throw QString("%1 don't match any register").arg(sentenceList[2]);
    if (mapForLabel.count(sentenceList[3]) == 0) throw QString("%1 don't match any Label").arg(sentenceList[3]);
    ui->textBrowser->insertPlainText(mapForType.value(sentenceList[0]));
    ui->textBrowser->insertPlainText(mapForRegister.value(sentenceList[2]));
    ui->textBrowser->insertPlainText(mapForRegister.value(sentenceList[1]));
    QString str;
    str = change_num_to_str(mapForLabel.value(sentenceList[3])-line-1,16);
//    ui->textBrowser->insertPlainText(":");
    ui->textBrowser->insertPlainText(str);
    ui->textBrowser->insertPlainText("\n");
}

void MainWindow::processTypeI_3(QStringList sentenceList,int line)
{
    if (sentenceList.size() != 3) throw QString("This line don't match numbers of I function");
    int index; //index of last "("
    index = sentenceList[2].lastIndexOf('(');
    if (index == -1) throw QString("'%1' The format is wrong ").arg(sentenceList[2]);

    QString regiterStr = sentenceList[2];
    regiterStr.remove(regiterStr.size()-1,1);
    regiterStr.remove(0,index+1);
    QString expressionStr = sentenceList[2];
    expressionStr.remove(index,expressionStr.size()-index);

    if (mapForRegister.count(regiterStr) == 0) throw QString("%1 don't match any register").arg(regiterStr);
    if (mapForRegister.count(sentenceList[1]) == 0) throw QString("%1 don't match any register").arg(sentenceList[1]);

    ui->textBrowser->insertPlainText(mapForType.value(sentenceList[0]));
    ui->textBrowser->insertPlainText(mapForRegister.value(regiterStr));
    ui->textBrowser->insertPlainText(mapForRegister.value(sentenceList[1]));

    QString str = replaceDefineStr(expressionStr);
//    qDebug() << str;
    str = processExpression(str);
    str = change_10_to_2(str,10,2,16);
//    ui->textBrowser->insertPlainText(":");
    ui->textBrowser->insertPlainText(str);
    ui->textBrowser->insertPlainText("\n");
}

void MainWindow::processTypeI_5(QStringList sentenceList, int line)
{   //  lui $reg, imm
    if (sentenceList.size() != 3) throw QString("Register list format error.");
    ui->textBrowser->insertPlainText(mapForType.value(sentenceList[0]));        //insert instruction opcode
    ui->textBrowser->insertPlainText(mapForRegister.value(sentenceList[1]));    //insert first reg
    ui->textBrowser->insertPlainText(EmptyFive);
    bool ok; unsigned int imm = sentenceList[2].toInt(&ok);     //if imm is a integer
    if (ok) {
        ui->textBrowser->insertPlainText(change_10_to_2(sentenceList[2],10,2,16));
    } else {       //else imm is a memory label
        if(mapForMemory.count(sentenceList[2]) == 0 ) throw QString("Label not defined.");
        ui->textBrowser->insertPlainText(
                    change_num_to_str( mapForMemory.value(sentenceList[2]) , 16 ) );
    }
    ui->textBrowser->insertPlainText("\n");
}

QString MainWindow::change_num_to_str(int number,int len)
{
    //change num to str2 base2:2
    //the format of @length: len
    QString ans,temp;
    temp = QString("%1").arg(number,len,2);
    if (temp.length() > len)
        temp.remove(0,temp.length()-len);
    ans = temp.replace(" ","0");
    return ans;
}

QString MainWindow::change_10_to_2(QString str, int base1, int base2, int len)
{
    //change str1 base1 to str2 base2
    //the format of @length: len
    QString ans,temp;
    bool ok;
    int num = str.toInt(&ok,base1);
//    qDebug() << num;
    if (!ok) throw QString("In this line %1 is not a number").arg(str);
    temp = QString("%1").arg(num,len,base2);
    if (len!=0 && temp.length() > len)
        temp.remove(0,temp.length()-len);
    ans = temp.replace(" ","0");
    return ans;
}

QString MainWindow::processAtomicBracket(QString atomicExpression)
{
    bool ok;
    atomicExpression.toInt(&ok);
    if (ok) return atomicExpression;
    int index = atomicExpression.indexOf(QRegExp("[/*]"));
    if (index != -1){
        int index1 = atomicExpression.indexOf(QRegExp("[/*+-]"),index+1);
        int index2 = atomicExpression.lastIndexOf(QRegExp("[/*+-]"),index-1);
        if (index1 == -1) index1 = atomicExpression.size();
        bool ok1,ok2;
        int m;
        int m1 = atomicExpression.mid(index2+1,index-index2-1).toInt(&ok1);
        int m2 = atomicExpression.mid(index+1,index1-index-1).toInt(&ok2);
        if (!ok1) throw QString("'%1' is not a right formatting of number").arg(atomicExpression.mid(index2+1,index-index2-1));
        if (!ok2) throw QString("'%1' is not a right formatting of number").arg(atomicExpression.mid(index+1,index1-index-1));
        if (atomicExpression[index] == '/')
            m = m1 / m2;
        else if (atomicExpression[index] == '*')
            m = m1 * m2;
        else throw QString("shenmegui");
        atomicExpression.replace(index2+1,index1-index2-1,QString::number(m));
        return processAtomicBracket(atomicExpression);
    }
    index = atomicExpression.indexOf(QRegExp("[+-]"),1);
    if (index != -1){
        int index1 = atomicExpression.indexOf(QRegExp("[/*+-]"),index+1);
        int index2 = atomicExpression.lastIndexOf(QRegExp("[/*+-]"),index-1);
        if (index1 == -1) index1 = atomicExpression.size();
        bool ok1,ok2;
        int m;
        int m1 = atomicExpression.mid(index2+1,index-index2-1).toInt(&ok1);
        int m2 = atomicExpression.mid(index+1,index1-index-1).toInt(&ok2);
        if (!ok1) throw QString("'%1' is not a right formatting of number").arg(atomicExpression.mid(index2+1,index-index2-1));
        if (!ok2) throw QString("'%1' is not a right formatting of number").arg(atomicExpression.mid(index+1,index1-index-1));
        if (atomicExpression[index] == '+')
            m = m1 + m2;
        else if (atomicExpression[index] == '-')
            m = m1 - m2;
        else throw QString("shenmegui");
        atomicExpression.replace(index2+1,index1-index2-1,QString::number(m));
        return processAtomicBracket(atomicExpression);
    }
}

QString MainWindow::processExpression(QString str)
{
    int index2;
    int index1;
    QString temp;
    while (true){
        bool ok;
        str.toInt(&ok);
        if (ok) return str;
        index1 = str.lastIndexOf("(");
        if (index1 != -1 ) index2 = str.indexOf(")",index1);
        else               index2 = str.indexOf(")");
        if (index1!=-1 && index2==-1) throw QString("In this line brackets () don't match");
        if (index1==-1 && index2!=-1) throw QString("In this line brackets () don't match");
        if (index1 != -1 && index2 != -1){
            temp = processAtomicBracket(str.mid(index1+1,index2-index1-1));
            str.replace(index1,index2-index1+1,temp);
        }
        else{
           str = processAtomicBracket(str);
        }
    }
}

void MainWindow::processMessageError(QString error, int line)
{
    ui->textBrowser->clear();
    QMessageBox::critical(this,error,QString("Line %1.\n%2").arg(QString::number(line))
                                                            .arg(error));
}

void MainWindow::on_pushButton_2_clicked()
{
    //save ui->textBrowser->toPlainText() into binary file
    //qDebug() << ui->textBrowser->toPlainText();
    QFileDialog dialog(this);
    dialog.setWindowModality(Qt::WindowModal);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.exec();
    QStringList files = dialog.selectedFiles();
    if (files.isEmpty()) {
        QMessageBox::warning(this,"save failed","you don't save file");
        return;
    }
    QString fileName = files.at(0);

    bool ok;
    QString s,s1;
    FILE *f;
    int i,j,len;
    short int a,b,c;
    s=ui->textBrowser->toPlainText();
    //qDebug() << s;
    const char *filecstr = fileName.toStdString().c_str();
    len=s.length()/33;
    f=fopen(filecstr,"wb");
    for (i=0;i<len;i++)
    {
        s1=s.mid(i*33,32);
        j=s1.toInt(&ok,2);
        a=0x0000|j;//right part short
        c=a;
        a=(a>>8)&0x00ff;
        c=c<<8;
        a=a|c;
        j=j>>16;//left part short
        b=0x0000|j;
        c=b;
        b=(b>>8)&0x00ff;
        c=c<<8;
        b=b|c;
        fwrite(&b,2,1,f);
        fwrite(&a,2,1,f); //fixed something.
    }
    fclose(f);
//    QFile file(fileName);
//    if (!file.open(QFile::WriteOnly)) {
//        QMessageBox::warning(this, tr("Application"),
//                             tr("Cannot write file %1:\n%2.")
//                             .arg(fileName)
//                             .arg(file.errorString()));
//        return;
//    }
//    QDataStream out(&file);
//    QStringList sentenceList = ui->textBrowser->toPlainText().split("\n",QString::SkipEmptyParts);
//    foreach (QString sentence,sentenceList){
//        bool ok;
//        //qDebug() << sentence.toInt(&ok,2);
//        out << quint32(sentence.toInt(&ok,2));
//    }
//    file.close();
}

void MainWindow::on_pushButton_5_clicked()
{
    //save data into binary file
    QFileDialog dialog(this);
    dialog.setWindowModality(Qt::WindowModal);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.exec();
    QStringList files = dialog.selectedFiles();
    if (files.isEmpty()) {
        QMessageBox::warning(this,"save failed","you don't save file");
        return;
    }
    QString fileName = files.at(0);
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly)) {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return;
    }
    QFile infile("./data");
    infile.open(QIODevice::ReadOnly);
    QDataStream out(&file);
    QDataStream in(&infile);
    qint8 temp;
    //in >> temp;
    int tempdis = 0x10000000;
    while (tempdis < memoryStart)
    {
        in >> temp;
        out << temp;
        tempdis += 1;
    }
    file.close();
    infile.close();
}

void MainWindow::on_pushButton_4_clicked()
{
//    MipsCPU tmpCPU;
//    qDebug() << "in run()" << endl;
//    tmpCPU.boot();
//    tmpCPU.run();
//    tmpCPU.showRegs();
//    tmpCPU.MMU->showMem();

    myCpu = new cpu;
    this->hide();
    myCpu->show();
}
