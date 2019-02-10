#ifndef AUCTIONSPACE_H
#define AUCTIONSPACE_H
#include "space.h"
#include <QObject>

class PropertyCard;

class AuctionSpace:public Space
{
    Q_OBJECT
public:
    AuctionSpace();
    void doSpaceMove(Board& board);
	void read(const QJsonObject &json);
    void write(QJsonObject &json) const;

private:
    static const int SIZE_OF_BOARD = 52;
    PropertyCard* searchUnownedProperty(Board& board)const;
signals:
    void auctionProperty();
};

#endif // AUCTIONSPACE_H
