/*
    Copyright (c) 2012, Almost23 (Almondy23@gmail.com)
    See COPYING for licensing information
*/

#include "header/patch.h"
#include "ui_patch.h"

patch::patch(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::patch)
{
    ui->setupUi(this);
}

patch::~patch()
{
    delete ui;
}

void patch::addPatch(int address, int value, int enabled){

}

void patch::removePatch(int address){

}

void patch::togglePatch(int address){

}

