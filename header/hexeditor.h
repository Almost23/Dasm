/*
    Copyright (c) 2012, Almost23 (Almondy23@gmail.com)
    See COPYING for licensing information
*/

#ifndef HEXEDITOR_H
#define HEXEDITOR_H

#include <QTableWidget>
#include <QHeaderView>
#include <QShortcut>
//#include <QItemSelectionModel>
#include "mainwindow.h"

class MainWindow;

class hexeditor : public QTableWidget
{
    Q_OBJECT
public:
    explicit hexeditor(QWidget *parent = 0);
    void init(MainWindow *Parent);
    void updateDisplay(int address);
    void syncHexEditor(int address);

public slots:
    void onEdit(QTableWidgetItem *item);

protected:
    QString fromAscii(char* string, unsigned int length);
    MainWindow *main;

};

#endif // HEXEDITOR_H
