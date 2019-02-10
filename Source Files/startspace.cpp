#include "startspace.h"
#include <QJsonObject>

StartSpace::StartSpace()
{
    type = START;
}



void StartSpace::doSpaceMove(Board& board)
{

}

/*  Author: Ho Yuet
 *  load
 */
void StartSpace::read(const QJsonObject &json)
{
    type = Type(qRound(json["type"].toDouble()));
}

/*  Author: Ho Yuet
 *  save
 */
void StartSpace::write(QJsonObject &json) const
{
    json["type"] = type;
}

