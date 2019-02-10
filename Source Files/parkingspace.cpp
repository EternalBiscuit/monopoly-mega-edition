#include "parkingspace.h"
#include <QJsonObject>

ParkingSpace::ParkingSpace()
{
    type = SPECIAL;
}

void ParkingSpace::doSpaceMove(Board& board)
{

}

/*
 * load
 */
void ParkingSpace::read(const QJsonObject &json)
{

    type = Type(qRound(json["type"].toDouble()));
}

/*
 *  Save
 */
void ParkingSpace::write(QJsonObject &json) const
{
    json["type"] = type;
}

