#ifndef PARKINGSPACE_H
#define PARKINGSPACE_H
#include "specialspace.h"

class ParkingSpace: public SpecialSpace
{
public:
    ParkingSpace();
    void doSpaceMove(Board& board);
    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;
};

#endif // PARKINGSPACE_H

