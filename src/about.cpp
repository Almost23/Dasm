/*
    Copyright (c) 2012, Almost23 (Almondy23@gmail.com)
    See COPYING for licensing information
*/

#include "header/about.h"
#include "ui_about.h"

about::about(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::about)
{
    ui->setupUi(this);
}

about::~about()
{
    delete ui;
}
