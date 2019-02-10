#ifndef SPECIALSPACE_H
#define SPECIALSPACE_H
#include "space.h"

class SpecialSpace: public Space
{
    Q_OBJECT
public:
    SpecialSpace();
    void doSpaceMove(Board& board) = 0;
    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;
};

#endif // SPECIALSPACE_H

