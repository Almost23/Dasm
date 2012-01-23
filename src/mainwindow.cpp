/*
    Copyright (c) 2012, Almost23 (Almondy23@gmail.com)
    See COPYING for licensing information
*/

#include "header/mainwindow.h"
#include "ui_mainwindow.h"

#define MAX_SIZE 0x3200000

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    QVector<int> vect; vect.append(0); vect.append(0);
    allData = new Data(this,NULL,0,vect);

    ui->HexEditor->init(this);
    ui->tableWidget->init(this);


    //Make sure both tables have been initialized before synchronization
    connect(ui->tableWidget, SIGNAL(currentCellChanged(int,int,int,int)), ui->tableWidget, SLOT(onSelectionChange(int,int, int, int)));

    QShortcut *shortcut;

    shortcut = new QShortcut(QKeySequence("Ctrl+J"), ui->lineEdit);
    connect(shortcut, SIGNAL(activated()), ui->lineEdit, SLOT(setFocus()));

    shortcut = new QShortcut(QKeySequence("Ctrl+F"), ui->lineEdit_2);
    connect(shortcut, SIGNAL(activated()), ui->lineEdit_2, SLOT(setFocus()));

    shortcut = new QShortcut(QKeySequence("Ctrl+D"), ui->tableWidget);
    shortcut->setContext(Qt::WidgetShortcut);
    connect(shortcut, SIGNAL(activated()), ui->tableWidget, SLOT(setDisplayFormat()));

    shortcut = new QShortcut(QKeySequence("Ctrl+W"), ui->tableWidget);
    shortcut->setContext(Qt::WidgetShortcut);
    connect(shortcut, SIGNAL(activated()), ui->tableWidget, SLOT(setDisplayFormat()));

    shortcut = new QShortcut(QKeySequence("Ctrl+H"), ui->tableWidget);
    shortcut->setContext(Qt::WidgetShortcut);
    connect(shortcut, SIGNAL(activated()), ui->tableWidget, SLOT(setDisplayFormat()));

    shortcut = new QShortcut(QKeySequence("Ctrl+B"), ui->tableWidget);
    shortcut->setContext(Qt::WidgetShortcut);
    connect(shortcut, SIGNAL(activated()), ui->tableWidget, SLOT(setDisplayFormat()));

    shortcut = new QShortcut(QKeySequence(Qt::Key_Up), ui->tableWidget);
    shortcut->setContext(Qt::WidgetShortcut);
    connect(shortcut, SIGNAL(activated()), ui->tableWidget, SLOT(shiftTable()));

    shortcut = new QShortcut(QKeySequence(Qt::Key_Down), ui->tableWidget);
    shortcut->setContext(Qt::WidgetShortcut);
    connect(shortcut, SIGNAL(activated()), ui->tableWidget, SLOT(shiftTable()));

    shortcut = new QShortcut(QKeySequence(Qt::Key_Up | Qt::Key_Control), ui->tableWidget);
    shortcut->setContext(Qt::WidgetShortcut);
    connect(shortcut, SIGNAL(activated()), ui->tableWidget, SLOT(shiftTable()));

    shortcut = new QShortcut(QKeySequence(Qt::Key_Down | Qt::Key_Control), ui->tableWidget);
    shortcut->setContext(Qt::WidgetShortcut);
    connect(shortcut, SIGNAL(activated()), ui->tableWidget, SLOT(shiftTable()));

}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::open(){
QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "",
           tr("Dasm Files (*.dsm *.ram *.bin);;All Files (*.*)"));

       if (fileName != "") {
           QFile file(fileName);
           if (!file.open(QIODevice::ReadOnly)) {
               QMessageBox::critical(this, tr("Error"),
                   tr("Could not open file"));
               return;
           }
           if(file.size() <= MAX_SIZE){
               loadfrom ld(this);
               ld.deleteLater();
               QVector<int> load(2);
               if( ld.exec() == QDialog::Accepted){
                   //get address offset and file offset from loadfrom window
                   load = ld.text();

                   //Arbitrary max file size of 50MB

                   //TODO: chunk file loading

                   file.seek(load.at(1));
                   allData->resetData(file.read(file.size()-load.at(1)).constData(), file.size()-load.at(1), load);

                   ui->tableWidget->updateDisplay(allData->getAddressOffset(),true);
                   ui->HexEditor->updateDisplay(allData->getAddressOffset());

               }
           }
           else{
               QMessageBox mBox;
               mBox.setWindowTitle("File too large!");
               mBox.setText(QString("%1 is too large!\n\nThe maximum file size is 0x%2 bytes.").arg(file.fileName()).arg(MAX_SIZE,7,16));
               mBox.setIcon(QMessageBox::Critical);
               mBox.exec();
           }


           file.close();

       }
}

void MainWindow::save(){
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Filename"), "",
                                                    tr("Binary Files (*.bin)"));

    if(fileName != "" ){
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, tr("Error"),
                tr("Could not open file"));
            return;
        }


        //TODO:
        // 1) Design Header
        // 2) Save the data
        // 3) allow to save raw binary data
        file.close();
    }
}

void MainWindow::about_wind(){
    about ab;
    ab.deleteLater();
    ab.exec();
}

void MainWindow::settings_wind(){
    settings st;
    st.deleteLater();
    if(st.exec() == QDialog::Accepted){

    }
    else{

    }

}

void MainWindow::patch_wind(){
    patch pt;
    pt.deleteLater();
    pt.exec();
}

void MainWindow::jumpAddress(){
    bool isHex = false;
    unsigned int address = ui->lineEdit->text().toInt(&isHex, 16);

    //Temporary word padding until an algo is implemented
    //to check the actual display type of the address specified
    //(short version: this assumes the target address should be displayed as a word)
    address -= address%4;
    if(isHex){
        ui->tableWidget->updateDisplay(address, true);
        ui->HexEditor->syncHexEditor(address);
    }

}

void MainWindow::search(){
    //Seach code here

}

void MainWindow::syncHexEditor(int address){
    //tableWidget does not have direct access to MainWindow's ui
    //This gives indirect access
    ui->HexEditor->syncHexEditor(address);
}

void MainWindow::syncTableWidget(int address){
    //HexEditor does not have direct access to MainWindow's ui
    //This gives indirect access
    ui->tableWidget->syncTableWidget(address);
}
