/*
    Copyright (c) 2012, Almost23 (Almondy23@gmail.com)
    See COPYING for licensing information
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QFile>
#include "header/about.h"
#include "header/loadfrom.h"
#include "header/patch.h"
#include "header/data.h"
#include "header/settings.h"
#include "header/tablewidget.h"

class tablewidget;
class hexEditor;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void syncHexEditor(int address);
    void syncTableWidget(int address);

    Data *allData;

public slots:
    void open();
    void save();
    void about_wind();
    void settings_wind();
    void patch_wind();
    void jumpAddress();
    void search();

protected:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
