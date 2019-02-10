#include "stationspace.h"
#include "railroadcard.h"
#include "propertycard.h"
#include "board.h"
#include "player.h"

StationSpace::StationSpace()
{

}

StationSpace::StationSpace(int newPrice, QString newName, QColor newColour)
    :PropertySpace(newPrice, newName, newColour)
{
    type = STATION;
}

void StationSpace::doSpaceMove(Board& board)
{
    QList<Player*> players = board.getPlayers();
    int currentTurn = board.getCurrentTurn();
    RailRoadCard* property = NULL;

    if (this->checkIfOwned() && this->getOwner() != players[currentTurn]->getNumberPlayer())
    {
        property = (RailRoadCard*)(players[this->getOwner()]->getPropertyCard(name));

        int rent = property->getRent(board.getNumberOfPlayerCards(*players[this->getOwner()], property->getColour()));

        players[currentTurn]->changeMoney(-rent);
        players[this->getOwner()]->changeMoney(rent);

        emit rentPaid(rent, this->getOwner());
    }
    else if (!(this->checkIfOwned()))
    {
        property = (RailRoadCard*)(board.getBankPropertyCard(name));

        emit stationIsBuyable(property->getName(), property->getValue(), property->getPriceMortgage(), property->getBuildingPrice(), false, board.getIndexSpaceFromPropertyName(name));
    }
}

void StationSpace::doAuction(Board& board)
{
    RailRoadCard* property = (RailRoadCard*)(board.getBankPropertyCard(name));

    emit stationIsBuyable(property->getName(), property->getValue(), property->getPriceMortgage(), property->getBuildingPrice(), true, board.getIndexSpaceFromPropertyName(name));
}

/*
 * Save
 */
void StationSpace::read(const QJsonObject &json)
{
    PropertySpace::read(json);
}

/*
 * Load
 */
void StationSpace::write(QJsonObject &json) const
{
    PropertySpace::write(json);
}

