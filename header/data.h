/*
    Copyright (c) 2012, Almost23 (Almondy23@gmail.com)
    See COPYING for licensing information
*/

#ifndef DATA_H
#define DATA_H

#include <QVector>
#include <QObject>


enum DISPLAY_TYPE{
    DISP_BYTE = 0,
    DISP_HALF = 1,
    DISP_WORD = 2,
    DISP_DWORD = 3
};

class Data : public QObject
{
    Q_OBJECT

public:
    Data(QWidget *Parent, const char* dat, qint64 Size, QVector<int> offsets);
    ~Data();

    uint   getAddressOffset();
    uint   getFileOffset();
    qint64 getSize();
    char*  getData(int address, int length);
    char*  getDisplayData(int address, int length);
    void   setAddressOffset(int offset);
    int    setDisplayData(int address, int type);
    void   resetData(const char* dat, qint64 Size, QVector<int> offsets);

protected:
    char* bin;       //Holds the contents of a loaded file
    char* display;   //Hold information on how to display a loaded file
    qint64 size;     //Size of loaded file
    uint   fOff;     //Offset in a loaded file from which to begin loading from
    uint   addrOff;  //Offset from 0 which is aliased to bin[0]
};

#endif // DATA_H
