#ifndef STATIONSPACE_H
#define STATIONSPACE_H
#include "propertyspace.h"

class StationSpace: public PropertySpace
{
    Q_OBJECT
public:
    StationSpace();
    StationSpace(int newPrice, QString newName, QColor newColour);
    void doSpaceMove(Board& board);
    void doAuction(Board& board);
    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;
signals:
    void stationIsBuyable(QString stationName, int price, int priceMortgage, int priceRailRoad, bool auction, int spaceIndex);
    void rentPaid(int rent, int owner)const;






};

#endif // STATIONSPACE_H
