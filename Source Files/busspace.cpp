#include "busspace.h"
#include "board.h"
#include <QJsonObject>

BusSpace::BusSpace()
{
    type = BUS;
}

void BusSpace::doSpaceMove(Board& board)
{
    board.addBusTicket();
}

/*  Author: Ho Yuet
 *  load
 */
void BusSpace::read(const QJsonObject &json)
{
    type = Type(qRound(json["type"].toDouble()));

}

/*  Author: Ho Yuet
 * save
 */
void BusSpace::write(QJsonObject &json) const
{
    json["type"] = type;
}

