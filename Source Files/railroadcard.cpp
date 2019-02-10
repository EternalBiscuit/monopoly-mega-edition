#include "railroadcard.h"
#include <QJsonObject>

RailRoadCard::RailRoadCard()
{

}

RailRoadCard::RailRoadCard(QString newName,QColor newColour, int newValue, int newRent, int newMortgage, int newPriceDepot)
    :PropertyCard(newName, newColour, newValue, newRent, newMortgage)
{
    priceRailDepot = newPriceDepot;
    hasRailDepot = false;
    type = PropertyCard::PropertyType::STATION;
}

int RailRoadCard::getRent(int number, int pips) const
{
    if (hasRailDepot)
        return priceRent*number*2;
    return priceRent*number;
}



void RailRoadCard::useCard()
{

}

int RailRoadCard::getBuildingPrice()
{
    return priceRailDepot;
}

/* Author: Ho Yuet
 * Returns if the amount of buildings it can build
 */
int RailRoadCard::getAmountBuildableBuildings()
{
    if(!hasRailDepot)
        return 1;
    return 0;
}

/*  Author: Ho Yuet
 * Checks if you can build a building
 */
bool RailRoadCard::canBuildBuildings(bool hasMonopoly)
{
    if(!hasRailDepot)
        return true;
    return false;
}

/*  Author: Ho Yuet
 *  Builds a building
 */
void RailRoadCard::buildBuilding()
{
    hasRailDepot = true;
}

int RailRoadCard::getAmountBuildings()
{
    return hasRailDepot;
}

int RailRoadCard::getNumberHotels()
{
    return 0;
}

int RailRoadCard::getNumberHouses()
{
    if (hasRailDepot)
    {
        return 1;
    }
}

void RailRoadCard::removeAllBuildings()
{
    hasRailDepot = false;
}

/*
 * Removes a building
 */
void RailRoadCard::removeBuilding()
{
    if (hasRailDepot)
        hasRailDepot = false;
}

/*
 * Checks if removing a building is possible
 */
bool RailRoadCard::canRemoveBuilding()
{
    if (hasRailDepot)
        return true;
    return false;
}

PropertyCard::TypeBuilding RailRoadCard::getTypeBuilding()
{
    return RAILDEPOT;
}

void RailRoadCard::write(QJsonObject &json) const
{
    PropertyCard::write(json);
    json["priceRailDepot"] = priceRailDepot;
    json["hasRailDepot"] = hasRailDepot;
}

void RailRoadCard::read(const QJsonObject &json)
{
    PropertyCard::read(json);
    priceRailDepot = json["priceRailDepot"].toInt();
    hasRailDepot = json["hasRailDepot"].toBool();
}



