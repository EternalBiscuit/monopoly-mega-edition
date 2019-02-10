#include "tojailcommunitycard.h"
#include "board.h"

ToJailCommunityCard::ToJailCommunityCard(QString newDescription)
    : CommunityChestCard(newDescription)
{

}

void ToJailCommunityCard::useCard(Board& board)
{
    emit usedCard(description, value);
    board.goToJail();
}
