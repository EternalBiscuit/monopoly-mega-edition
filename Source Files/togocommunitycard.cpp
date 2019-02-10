#include "togocommunitycard.h"
#include "board.h"

ToGoCommunityCard::ToGoCommunityCard(QString newDescription)
    : CommunityChestCard(newDescription)
{

}

void ToGoCommunityCard::useCard(Board& board)
{
    emit usedCard(description, value);

    board.goToStart();

}
