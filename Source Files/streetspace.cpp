// Author: Ho Yuet
#include "streetspace.h"
#include "player.h"
#include "board.h"
#include "streetcard.h"
#include <QDebug>

StreetSpace::StreetSpace()
{

}

/*
 * Constructor of StreetSpace
 * 3 arguments: price, name, colour
 */
StreetSpace::StreetSpace(int newPrice, QString newName, QColor newColour)
    :PropertySpace(newPrice, newName, newColour)
{
    type = STREET;
    isOwned = false;
}

/*
 * Prompt buying or renting
 */
void StreetSpace::doSpaceMove(Board& board)
{
    QList<Player*> players = board.getPlayers();
    int currentTurn = board.getCurrentTurn();
    StreetCard* property = NULL;

    if (this->checkIfOwned() && this->getOwner() != players[currentTurn]->getNumberPlayer())
    {
        property = (StreetCard*)(players[this->getOwner()]->getPropertyCard(name));

        int rent = property->getRent();

        if (board.checkHasFullMonopoly(*players[currentTurn], property->getColour()))
            rent *= 3;
        else if (board.checkHasMajority(*players[currentTurn], property->getColour()))
            rent *= 2;

        players[currentTurn]->changeMoney(-rent);
        players[this->getOwner()]->changeMoney(rent);

        emit rentPaid(rent, this->getOwner());
    }
    else if (!(this->checkIfOwned()))
    {
        property = (StreetCard*)(board.getBankPropertyCard(name));

        emit streetIsBuyable(name, price, property->getPriceRent(), property->getPriceMortgage(), property->getBuildingPrice(), property->getOneHouseRentPrice(), property->getTwoHouseRentPrice(),
                        property->getThreeHouseRentPrice(), property->getFourHouseRentPrice(), property->getHotelRent(), property->getSkyscraperRent(), false, board.getIndexSpaceFromPropertyName(name));
    }
}

void StreetSpace::doAuction(Board& board)
{
    StreetCard* property = (StreetCard*)(board.getBankPropertyCard(name));

    emit streetIsBuyable(name, price, property->getPriceRent(), property->getPriceMortgage(), property->getBuildingPrice(), property->getOneHouseRentPrice(), property->getTwoHouseRentPrice(),
                    property->getThreeHouseRentPrice(), property->getFourHouseRentPrice(), property->getHotelRent(), property->getSkyscraperRent(), true, board.getIndexSpaceFromPropertyName(name));
}

/*
 * load
 */
void StreetSpace::read(const QJsonObject &json)
{
    PropertySpace::read(json);
}

/*
 * save
 */
void StreetSpace::write(QJsonObject &json) const
{
    PropertySpace::write(json);
}


