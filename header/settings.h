/*
    Copyright (c) 2012, Almost23 (Almondy23@gmail.com)
    See COPYING for licensing information
*/

#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>

namespace Ui {
    class settings;
}

class settings : public QDialog
{
    Q_OBJECT

public:
    explicit settings(QWidget *parent = 0);
    ~settings();

protected:
    Ui::settings *ui;
};

#endif // SETTINGS_H
