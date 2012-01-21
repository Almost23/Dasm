#ifndef STRUCTS_H
#define STRUCTS_H

#include <QObject>

class dat : public QObject
{
    Q_OBJECT
public:
    int length;
    int addrOff;
    int fOff;
    const char* bin;
};


#endif // STRUCTS_H
