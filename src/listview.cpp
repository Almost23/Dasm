#include "listview.h"
#include <QListView>
#include <QStringListModel>

listview::listview(QWidget *parent) : QListView(parent)
{
    this->setAlternatingRowColors(true);


}



