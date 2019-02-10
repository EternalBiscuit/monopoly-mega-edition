#include "chancespace.h"
#include <QJsonObject>
#include "board.h"
#include "communitychestcard.h"

ChanceSpace::ChanceSpace()
{
    type = CHANCE;
}

void ChanceSpace::doSpaceMove(Board& board)
{
    board.getRandomCommChestCard()->useCard(board);
}

/*  Author: Ho Yuet
 * save
 */
void ChanceSpace::read(const QJsonObject &json)
{
    type = Type(qRound(json["type"].toDouble()));
}

/*  Author: Ho Yuet
 *  load
 */
void ChanceSpace::write(QJsonObject &json) const
{
    json["type"] = type;
}

