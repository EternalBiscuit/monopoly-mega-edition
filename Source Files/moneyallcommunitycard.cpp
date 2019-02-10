#include "moneyallcommunitycard.h"
#include "board.h"
#include "player.h"

MoneyAllCommunityCard::MoneyAllCommunityCard(QString newDescription, int newValue)
    : CommunityChestCard(newDescription, newValue)
{

}

void MoneyAllCommunityCard::useCard(Board& board)
{
    QList<Player*> players = board.getPlayers();

    foreach (Player* player, players)
    {
        if (player->getNumberPlayer() != board.getCurrentTurn())
        {
            player->changeMoney(-value);
            players[board.getCurrentTurn()]->changeMoney(value);
        }
    }

    emit usedCard(description, value);
}
