#ifndef RAILROADCARD_H
#define RAILROADCARD_H
#include "propertycard.h"

class RailRoadCard: public PropertyCard
{
    Q_OBJECT
public:
    RailRoadCard();
    RailRoadCard(QString newName,QColor newColour, int newValue, int newRent, int newMortgage, int newPriceDepot);
    int getRent(int number = 0, int pips = 0)const;
    void useCard();
    int getBuildingPrice();
    int getAmountBuildableBuildings();
    bool canBuildBuildings(bool hasMonopoly);
    void buildBuilding();
    int getAmountBuildings();
    int getNumberHotels();
    int getNumberHouses();
    void removeAllBuildings();
void removeBuilding();
    bool canRemoveBuilding();
    PropertyCard::TypeBuilding getTypeBuilding();

    void write(QJsonObject &json)const;
    void read(const QJsonObject &json);

private:
    int priceRailDepot;
    bool hasRailDepot;

};

#endif // RAILROADCARD_H
