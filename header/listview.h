#ifndef LISTVIEW_H
#define LISTVIEW_H

#include <QListView>

class listview: public QListView
{
    Q_OBJECT

public:
    explicit listview(QWidget *parent);
};

#endif // LISTVIEW_H
