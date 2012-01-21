/*
    Copyright (c) 2012, Almost23 (Almondy23@gmail.com)
    See COPYING for licensing information
*/

#include "header/tablewidget.h"

tablewidget::tablewidget(QWidget *Parent) : QTableWidget(Parent)
{

}

void tablewidget::init(MainWindow *Parent){
    horizontalHeader()->setClickable(false);
    horizontalHeader()->setResizeMode(QHeaderView::Fixed);
    setColumnWidth(1,columnWidth(0)*2);
    horizontalHeader()->setResizeMode(2,QHeaderView::Stretch);
    horizontalHeader()->setResizeMode(3,QHeaderView::Stretch);
    horizontalHeader()->setResizeMode(4,QHeaderView::Stretch);

    verticalHeader()->setResizeMode(QHeaderView::Stretch);

    connect(this, SIGNAL(cellChanged(int, int)), SLOT(validateChange(int,int)));

    for(int i=0;i<rowCount();i++){
        for(int j=0; j<2; j++){
                item(i,j)->setTextAlignment(Qt::AlignCenter);
                item(i,j)->setForeground(Qt::gray);
                item(i,j)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        }
    }

    main = Parent;
    patchMap.setInsertInOrder(true);
}

void tablewidget::validateChange(int row, int column){

}


void tablewidget::setDisplayFormat(){
    QShortcut *shortcut = (QShortcut*)QObject::sender();
    QKeySequence key = shortcut->key();

    unsigned int address = item(currentRow(),0)->text().toUInt(NULL, 16);
    int selection=0;

    if(address >= main->allData->getAddressOffset() && address < main->allData->getAddressOffset() + main->allData->getSize()){
        if(key.matches(QKeySequence("Ctrl+D"))){
            selection = main->allData->setDisplayData(address, DISP_DWORD);
        }
        else if(key.matches(QKeySequence("Ctrl+W"))){
            selection = main->allData->setDisplayData(address, DISP_WORD);
        }
        else if(key.matches(QKeySequence("Ctrl+H"))){
            selection = main->allData->setDisplayData(address, DISP_HALF);
        }
        else if(key.matches(QKeySequence("Ctrl+B"))){
            selection = main->allData->setDisplayData(address, DISP_BYTE);
        }

        updateDisplay(item(0,0)->text().toUInt(0,16));

        setCurrentCell(findItems(QString("%1").arg(selection, 8, 16, QChar('0')), Qt::MatchExactly).first()->row(), currentColumn(), QItemSelectionModel::ClearAndSelect);

    }
}

void tablewidget::onSelectionChange(int new_row, int new_column, int old_row, int old_column){

    int address = item(new_row, 0)->text().toUInt(NULL, 16);
    main->syncHexEditor(address);
}

void tablewidget::syncTableWidget(int address){

}

void tablewidget::updateDisplay(int address){
    char* displayInfo = new char[rowCount()];
    displayInfo = main->allData->getDisplayData(address, rowCount());
    int dataSize = 0;
    for(int i=0; i<rowCount(); i++){
        dataSize += displayInfo[i];
    }
    char* data = new char[dataSize];
    data = main->allData->getData(address, dataSize);
    if(data != NULL){
        quint64 temp;
        uint index = 0;
        for(int i=0; i<rowCount(); index+=displayInfo[i], i++){
            temp = 0;
            memcpy(&temp, &data[index], displayInfo[i]);
            item(i,0)->setText(QString("%1").arg(address+index, 8, 16, QChar('0')));
            item(i,1)->setText(QString("%1").arg(temp, displayInfo[i]*2, 16, QChar('0')));

            if(address+index >= main->allData->getAddressOffset()+main->allData->getSize()
                    || address+index < main->allData->getAddressOffset()){
                item(i,0)->setForeground(Qt::gray);
                item(i,1)->setForeground(Qt::gray);
                item(i,1)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
            }
            else{
                item(i,0)->setForeground(Qt::black);
                item(i,1)->setForeground(Qt::black);
                item(i,1)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable);
            }
        }
    }
    setCurrentCell(0,currentColumn(),QItemSelectionModel::ClearAndSelect);
    delete[] data;
    delete[] displayInfo;
}

void tablewidget::shiftTable(){
    QShortcut *shortcut = (QShortcut*)QObject::sender();
    QKeySequence key = shortcut->key();

    //Shift the table towards higher addresses
    if(key.matches(QKeySequence(Qt::Key_Down))){
        if(currentRow() == rowCount()-1 ){
            updateDisplay(item(1,0)->text().toUInt(0,16));
            setCurrentCell(rowCount()-1,currentColumn(), QItemSelectionModel::ClearAndSelect);
            //For some reason the sync must be forced here or it doesn't work properly.
            main->syncHexEditor(item(rowCount()-1,0)->text().toUInt(0,16));
        }
        else setCurrentCell(currentRow()+1,currentColumn(), QItemSelectionModel::ClearAndSelect);
    }

    //Shift the table towards lower addresses
    else if(key.matches(QKeySequence(Qt::Key_Up))){
        if(currentRow() == 0){           
            int address = item(0,0)->text().toUInt(0,16);
            updateDisplay(address-main->allData->getDisplayData(address-1,1)[0]);
            main->syncHexEditor(item(currentRow(),0)->text().toUInt(0,16));
        }
        else setCurrentCell(currentRow()-1,currentColumn(), QItemSelectionModel::ClearAndSelect);
    }

}

