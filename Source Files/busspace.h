#ifndef BUSSPACE_H
#define BUSSPACE_H
#include "cardspace.h"

class BusSpace: public CardSpace
{
public:
    BusSpace();
    void doSpaceMove(Board& board);
    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;
};

#endif // BUSSPACE_H

