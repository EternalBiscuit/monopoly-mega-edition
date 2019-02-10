#include "moneypropcommunitycard.h"
#include "board.h"
#include "player.h"
#include "propertycard.h"
#include "streetcard.h"
#include "railroadcard.h"

MoneyPropCommunityCard::MoneyPropCommunityCard(QString newDescription)
    : CommunityChestCard(newDescription)
{

}

void MoneyPropCommunityCard::useCard(Board& board)
{
    QList<Player*> players = board.getPlayers();

    QList<PropertyCard*> properties = players[board.getCurrentTurn()]->getProperties();

    int numberHouses = 0, numberHotels = 0;

    foreach (PropertyCard* property, properties)
    {
        numberHouses += property->getNumberHouses();
        numberHotels += property->getNumberHotels();
    }

    players[board.getCurrentTurn()]->changeMoney(-((numberHouses*HOUSE_COST) + (numberHotels*HOTEL_COST)));

    emit usedCard(description, value);

}
