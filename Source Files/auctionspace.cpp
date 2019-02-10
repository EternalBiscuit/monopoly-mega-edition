#include "auctionspace.h"
#include "board.h"
#include "player.h"
#include "space.h"
#include "propertycard.h"
#include "propertyspace.h"
#include <QJsonObject>


AuctionSpace::AuctionSpace()
{
    type = AUCTION;
}

void AuctionSpace::doSpaceMove(Board& board)
{    
    PropertyCard* unownedCard = searchUnownedProperty(board);
    int space = board.getIndexSpaceFromPropertyName(unownedCard->getName());

    if (unownedCard == NULL)
    {
        return;
    }
    else
    {
        PropertySpace* unownedSpace = (PropertySpace*)board.getSpaces()[space];
        unownedSpace->doAuction(board);
    }
}

PropertyCard* AuctionSpace::searchUnownedProperty(Board& board) const
{
    QList<PropertyCard*> cards = board.getBankPropertyCards();

    if (cards.isEmpty())
    {
        return NULL;
    }
    else
    {
        int index = rand() % cards.count();

        return cards[index];
    }
}

/*  Author: Ho Yuet
 *  load
 */
void AuctionSpace::read(const QJsonObject &json)
{
    type = Type(qRound(json["type"].toDouble()));

}

/*  Author: Ho Yuet
 * save
 */
void AuctionSpace::write(QJsonObject &json) const
{
    json["type"] = type;
}



