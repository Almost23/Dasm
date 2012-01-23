/*
    Copyright (c) 2012, Almost23 (Almondy23@gmail.com)
    See COPYING for licensing information
*/

#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QTableWidget>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QVector>
#include "header/mainwindow.h"

#define rows 24
#define columns 5
#define defaultDisplay 4

#define DISP_BYTE 0
#define DISP_HALF 1
#define DISP_WORD 2
#define DISP_DWORD 3

class MainWindow;

class tablewidget : public QTableWidget
{
    Q_OBJECT

public:
    explicit tablewidget(QWidget *parent = 0);
    void init(MainWindow *Parent);
    void updateDisplay(int address, bool updateSelection);
    void syncTableWidget(int address);
    QMap<int, QPair<int,bool> > patchMap; // <addr, <val, enabled> >

    //Reimplementation
    void resizeEvent(QResizeEvent *event);

public slots:
    void validateChange(int row, int column);
    void onSelectionChange(int new_row, int new_column, int old_row, int old_column);
    //void onResize();
    void shiftTable();
    void setDisplayFormat();

protected:
    MainWindow *main;
};

#endif // TABLEWIDGET_H
