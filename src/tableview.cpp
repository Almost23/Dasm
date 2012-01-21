#include "tableview.h"
#include <QTableView>
#include <QTableWidget>
#include <QStandardItemModel>

tableview::tableview(QWidget *parent) : QTableView(parent)
{

    this->setShowGrid(false);



    QStandardItemModel *model = new QStandardItemModel(5,5);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Address"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Value"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Instruction"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Label"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Comment"));





    this->setModel(model);
    this->setAlternatingRowColors(true);

}
