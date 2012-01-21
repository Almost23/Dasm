#include "tabwidget.h"
#include <QTabWidget>
#include <QAction>
#include <QKeySequence>

tabwidget::tabwidget(QWidget *parent) : QTabWidget(parent)
{
    tabs.append(new QWidget(this));
    tabs.append(new QWidget(this));



    this->addTab(tabs.takeFirst(), "EMPTY");
    this->addTab(tabs.takeLast(), "+");
}

void tabwidget::TabChanged(){

}

void tabwidget::closeTab(){

}

void tabwidget::newTab(){


}
