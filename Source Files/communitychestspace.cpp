#include "communitychestspace.h"
#include "board.h"
#include "communitychestcard.h"
#include <QJsonObject>


CommunityChestSpace::CommunityChestSpace()
{
    type = CHEST;
}

void CommunityChestSpace::doSpaceMove(Board& board)
{
    board.getRandomCommChestCard()->useCard(board);
}

/*
 * Load
 */
void CommunityChestSpace::read(const QJsonObject &json)
{
    type = Type(qRound(json["type"].toDouble()));
}

/*
 * Save
 */
void CommunityChestSpace::write(QJsonObject &json) const
{
    json["type"] = type;
}


