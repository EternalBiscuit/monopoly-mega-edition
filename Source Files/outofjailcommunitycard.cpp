#include "outofjailcommunitycard.h"
#include "player.h"
#include "board.h"

OutOfJailCommunityCard::OutOfJailCommunityCard(QString newDescription)
    : CommunityChestCard(newDescription)
{

}

void OutOfJailCommunityCard::useCard(Board& board)
{
    QList<Player*> players = board.getPlayers();

    players[board.getCurrentTurn()]->addJailCard();

    emit usedCard(description, value);
}
