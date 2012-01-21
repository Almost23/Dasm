/*
    Copyright (c) 2012, Almost23 (Almondy23@gmail.com)
    See COPYING for licensing information
*/

#ifndef LOADFROM_H
#define LOADFROM_H

#include <QDialog>
#include <QLineEdit>

namespace Ui {
    class loadfrom;
}

class loadfrom : public QDialog
{
    Q_OBJECT

public:
    explicit loadfrom(QWidget *parent = 0);
    ~loadfrom();

    QVector<int> text();

protected slots:
    void edit();

protected:
    Ui::loadfrom *ui;

};

#endif // LOADFROM_H
