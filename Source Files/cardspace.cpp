#include "cardspace.h"
#include <QJsonObject>

CardSpace::CardSpace()
{

}

void CardSpace::doSpaceMove(Board& board)
{

}
/*  Author: Ho Yuet
 *  load
 */
void CardSpace::read(const QJsonObject &json)
{
    type = Type(qRound(json["type"].toDouble()));
}
/*  Author: Ho Yuet
 *  save
 */
void CardSpace::write(QJsonObject &json) const
{
    json["type"] = type;
}


