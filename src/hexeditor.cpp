/*
    Copyright (c) 2012, Almost23 (Almondy23@gmail.com)
    See COPYING for licensing information
*/

#include "header/hexeditor.h"

hexeditor::hexeditor(QWidget *parent) :
    QTableWidget(parent)
{

}

void hexeditor::init(MainWindow *Parent){
    //A few hex editor options that aren't available through the Forms Editor
    horizontalHeader()->setClickable(false);
    verticalHeader()->setClickable(false);
    horizontalHeader()->setResizeMode(QHeaderView::Fixed);
    verticalHeader()->setResizeMode(QHeaderView::Fixed);

    for(int i =0; i<rowCount(); i++){
        item(i,columnCount()-1)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    }

    //For some reason, the horizontal header always adopts the default font
    horizontalHeader()->setFont(QFont(QString("Courier New"), 7));
    for(int i=0; i < rowCount(); i++){
        for(int j=0; j<columnCount(); j++){
            item(i,j)->setTextAlignment(Qt::AlignCenter);
        }
    }
    main = Parent;
}

void hexeditor::syncHexEditor(int address){
    int row = -1;
    int column;
    for(int i =0; i < rowCount(); i++){
        column = address - verticalHeaderItem(i)->text().toUInt(0,16);

        //address < smallest address in table
        if(column < 0){
            if(address>0){updateDisplay(address-address%16);
                          column = address%16;}
            else{         updateDisplay(address-(address%16+16));
                          column = address%16+16;}
            row = 0;
            break;
        }

        //Address is between min and max addresses on row i
        else if(column >= 0 && column < 16){
            row = i;
            break;
        }
    }

    //Address > Largest address in table
    if(row < 0){
        updateDisplay(address-qAbs(address%16)-16*3);
        row = rowCount()-1;
        column = 0;
    }

    setCurrentCell(row, column, QItemSelectionModel::ClearAndSelect);

}

void hexeditor::onEdit(QTableWidgetItem *item){

}

//Returns a subset of Ascii with '.' in place of any stripped values
QString hexeditor::fromAscii(char* string, unsigned int length){
    QString ret;
    for(unsigned int i=0; i<length; i++){
        if(string[i] >= 0x20 && string[i] <= 0x7e)
            ret[i] = ' ' + (string[i]-0x20);
        else
            ret[i] = '.';
    }
    return ret;
}

void hexeditor::updateDisplay(int address){
    char *dat = main->allData->getData(address,(columnCount()-1)*rowCount());

    //Populate the header
    for(int j =0; j <4; j++, address+=16){
        verticalHeaderItem(j)->setText(QString("%1").arg(address&0xFFFFFFFF, 8, 16, QChar('0')));
    }

    //Populate the table
    for(int i=0; i<rowCount(); i++){
        for(int j = 0; j<columnCount()-1; j++){
            item(i,j)->setText(QString("%1").arg((unsigned char)dat[i*16+j], 2, 16, QChar('0')));
        }
    }

    char* temp;
    for(int i =0; i<4; i++){
        temp = new char[16];
        for(int j =0; j<16; j++){
            temp[j] = dat[i*16+j];
        }
        //Swap comments on the following lines to switch from a subset of ascii with '.' to all ascii
        item(i, columnCount()-1)->setText(fromAscii(temp,16));
        //item(i,columnCount()-1)->setText(QString().fromAscii(temp,16));

        delete[] temp;
    }
}
