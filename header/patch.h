/*
    Copyright (c) 2012, Almost23 (Almondy23@gmail.com)
    See COPYING for licensing information
*/

#ifndef PATCH_H
#define PATCH_H

#include <QDialog>

namespace Ui {
    class patch;
}

class patch : public QDialog
{
    Q_OBJECT

public:
    explicit patch(QWidget *parent = 0);
    ~patch();

    void addPatch(int address, int value, int enabled);
    void removePatch(int address);
    void togglePatch(int address);

private:
    Ui::patch *ui;
};

#endif // PATCH_H
