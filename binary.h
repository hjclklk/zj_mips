#ifndef BINARY_H
#define BINARY_H
#include <QTextStream>
#include <QString>
#include <QMap>

class Binary
{
    static QMap<QString, QString> registers;
    static QMap<QString, int> opTypes;
    static QMap<int, int> labels;
    static int def;

    static QString I_type(QString code);
    static QString R_type(QString code);
    static QString J_type(QString code);

    static QMap<QString, QString> RTypes;
    static QMap<QString, QString> ITypes;
    static QMap<QString, QString> JTypes;
    static QMap<QString, QString> opCode;
    static QMap<QString, QString> functCode;

public:
    Binary();
    ~Binary();

    static void init();
    static QString binaryToMips(QString binaryCode);
};

#endif // BINARY_H
