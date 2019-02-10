// Author: Ho Yuet
#ifndef STREETSPACE_H
#define STREETSPACE_H
#include "space.h"
#include <QColor>
#include "propertyspace.h"
class Building;

class StreetSpace: public PropertySpace
{
    Q_OBJECT
public:
    StreetSpace();
    StreetSpace(int newPrice, QString newName, QColor newColour);
    void doSpaceMove(Board& board); // buying or renting
    void doAuction(Board& board);
void read(const QJsonObject &json);
    void write(QJsonObject &json) const;

private:
    //QList<Building*> buildings;
signals:
    void streetIsBuyable(QString streetName, int price, int rent, int priceMortgage, int buildingPrice, int oneHouseRent, int twoHouseRent,
                        int threeHouseRent, int fourHouseRent, int hotelRent, int skyRent, bool auction, int spaceIndex);
    void rentPaid(int rent, int owner)const;


};

#endif // STREETSPACE_H
