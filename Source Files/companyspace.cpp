#include "companyspace.h"
#include "board.h"
#include "player.h"
#include "companycard.h"

CompanySpace::CompanySpace()
{

}

CompanySpace::CompanySpace(int newValue, QString newName, QColor newColor)
    : PropertySpace(newValue, newName, newColor)
{
    type = COMPANY;
}

void CompanySpace::doSpaceMove(Board& board)
{
    QList<Player*> players = board.getPlayers();
    int currentTurn = board.getCurrentTurn();
    CompanyCard* property = NULL;

    if (this->checkIfOwned() && this->getOwner() != players[currentTurn]->getNumberPlayer())
    {
        property = (CompanyCard*)(players[this->getOwner()]->getPropertyCard(name));

        int rent = property->getRent(board.getNumberOfPlayerCards(*players[this->getOwner()], property->getColour()), board.getPips());

        players[currentTurn]->changeMoney(-rent);
        players[this->getOwner()]->changeMoney(rent);

        emit rentPaid(rent, this->getOwner());

    }
    else if (!(this->checkIfOwned()))
    {
        property = (CompanyCard*)(board.getBankPropertyCard(name));

        emit companyIsBuyable(name, price, property->getPriceMortgage(), false, board.getIndexSpaceFromPropertyName(name));
    }
}

void CompanySpace::doAuction(Board& board)
{
    PropertyCard* property = board.getBankPropertyCard(name);

    emit companyIsBuyable(name, price, property->getPriceMortgage(), true, board.getIndexSpaceFromPropertyName(name));
}

/*
 * Load
 */
void CompanySpace::read(const QJsonObject &json)
{
    PropertySpace::read(json);
}

/*
 * Save
 */
void CompanySpace::write(QJsonObject &json) const
{
    PropertySpace::write(json);
}

