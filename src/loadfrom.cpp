/*
    Copyright (c) 2012, Almost23 (Almondy23@gmail.com)
    See COPYING for licensing information
*/

#include "loadfrom.h"
#include "ui_loadfrom.h"

loadfrom::loadfrom(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loadfrom)
{

    ui->setupUi(this);
    this->setWindowTitle(tr("Load From"));

}

loadfrom::~loadfrom()
{

    delete ui;
}

void loadfrom::edit(){
    QLineEdit *edit = (QLineEdit*)QObject::sender();
    bool isHex = false;

    unsigned int temp;
    temp = edit->text().toUInt(&isHex, 16);
    if(!isHex){
        edit->setText("00000000");
    }
    else
        edit->setText(QString("%1").arg(temp, 8,16,QChar('0')));
}

QVector<int> loadfrom::text(){
    QVector<int> ret;

    ret.append(this->ui->lineEdit->text().toUInt(0,16));
    ret.append(this->ui->lineEdit_2->text().toUInt(0,16));
    return ret;
}
