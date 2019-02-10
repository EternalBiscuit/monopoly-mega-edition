#include "moneycommunitycard.h"
#include "board.h"
#include "player.h"

MoneyCommunityCard::MoneyCommunityCard(QString newDescription, int newValue)
    : CommunityChestCard(newDescription, newValue)
{

}

void MoneyCommunityCard::useCard(Board& board)
{
    QList<Player*> players = board.getPlayers();

    players[board.getCurrentTurn()]->changeMoney(value);

    emit usedCard(description, value);
}
