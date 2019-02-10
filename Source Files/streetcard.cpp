#include "streetcard.h"
#include <QDebug>
#include <QJsonObject>

StreetCard::StreetCard()
{

}

StreetCard::StreetCard(QString newName,QColor newColour, int newValue, int newRent, int newMortgage, int newBuildingPrice,
                       int oneHousePrice, int twoHousePrice, int threeHousePrice, int fourHousePrice, int oneHotelPrice, int oneSkyPrice)
    :PropertyCard(newName, newColour, newValue, newRent, newMortgage)
{
    buildingPrice = newBuildingPrice;
    priceRentOneHouse = oneHousePrice;
    priceRentTwoHouse = twoHousePrice;
    priceRentThreeHouse = threeHousePrice;
    priceRentFourHouse = fourHousePrice;
    priceRentWithHotel= oneHotelPrice;
    priceRentWithSkyscraper = oneSkyPrice;
    type = PropertyCard::PropertyType::STREET;
    hasHotel = false;
    hasSkyscraper = false;
    numberHouses = 0;

}

PropertyCard::TypeBuilding StreetCard::getTypeBuilding()
{
    if (hasHotel)
        return HOTEL;
    else if(hasSkyscraper)
        return SKYSCRAPER;
    else
        return HOUSE;
}


/*  Author: Ho Yuet
 * builds a house
 */
void StreetCard::buildHouse()
{
    numberHouses++;

}

/*  Author: Ho Yuet
 * builds a hotel and removes the houses
 */
void StreetCard::buildHotel()
{
    numberHouses = 0;
    hasHotel = true;
}

/*  Author: Ho Yuet
 * builds a skyscraper and removes the hotel
 */
void StreetCard::buildSkyscraper()
{
    hasHotel = false;
    hasSkyscraper = true;
}

int StreetCard::getRent(int number, int pips) const
{

    if (numberHouses > 0)
    {
        switch (numberHouses) {
        case 1:
            return priceRentOneHouse;
            break;
        case 2:
            return priceRentTwoHouse;
            break;
        case 3:
            return priceRentThreeHouse;
            break;
        case 4:
            return priceRentFourHouse;
            break;
        }
    }
    else if (hasHotel)
    {
        return priceRentWithHotel;
    }
    else if (hasSkyscraper)
    {
        return priceRentWithSkyscraper;
    }
    else
    {
        return priceRent;
    }


}

void StreetCard::useCard()
{

}

int StreetCard::getBuildingPrice()
{
    return buildingPrice;
}

int StreetCard::getOneHouseRentPrice()
{
    return priceRentOneHouse;
}

int StreetCard::getTwoHouseRentPrice()
{
    return priceRentTwoHouse;
}

int StreetCard::getThreeHouseRentPrice()
{
    return priceRentThreeHouse;
}

int StreetCard::getFourHouseRentPrice()
{
    return priceRentFourHouse;
}

int StreetCard::getHotelRent()
{
    return priceRentWithHotel;
}

int StreetCard::getSkyscraperRent()
{
    return priceRentWithSkyscraper;
}

/* Author: Ho Yuet
 * Returns if the amount of buildings it can build
 */
int StreetCard::getAmountBuildableBuildings()
{
    if (hasHotel && !hasSkyscraper) // if the skyscraper is missing
        return 1;
    if (!hasHotel && numberHouses == 4) // if it has 4 houses
        return 1;
    if(!hasHotel && !hasSkyscraper) // if there is no hotel or skyscraper
        return 4 - numberHouses;
    return 0;
}

/*  Author: Ho Yuet
 * Checks if you can build a building
 */
bool StreetCard::canBuildBuildings(bool hasMonopoly)
{
    if (!hasSkyscraper && hasHotel && !hasMonopoly && numberHouses == 0)
        return false;
    if(!hasHotel || numberHouses < 4)
        return true;
    return false;
}

/*  Author: Ho Yuet
 *  Builds a building
 */
void StreetCard::buildBuilding()
{
    if(numberHouses < 4 && !hasHotel && !hasSkyscraper)
    {
        buildHouse();
        return;
    }
    else if(numberHouses == 4)
    {
        buildHotel();
        return;
    }
    else if(hasHotel)
    {
        buildSkyscraper();
        return;
    }
}


int StreetCard::getAmountBuildings()
{
    if(hasHotel)
        return MAXHOTELS;
    if(hasSkyscraper)
        return MAXSKYSCRAPERS;
    return numberHouses;
}

int StreetCard::getNumberHotels()
{
    if (hasHotel)
    {
        return 1;
    }
}

int StreetCard::getNumberHouses()
{
    return numberHouses;
}

void StreetCard::removeAllBuildings()
{
    numberHouses = 0;
    hasHotel = false;
    hasSkyscraper = false;
}

/*
 * Removes a building
 */
void StreetCard::removeBuilding()
{
    if (hasSkyscraper)
    {
        hasSkyscraper = false;
        hasHotel = true;
    }
    else if(hasHotel)
    {
        hasHotel = false;
        numberHouses = MAX_AMOUNT_HOUSES;
    }
    else if (numberHouses > 0)
        numberHouses--;
}

/*
 * Checks if removing a building is possible
 * returns true if so
 */
bool StreetCard::canRemoveBuilding()
{
    if (hasSkyscraper || hasHotel || numberHouses > 0)
        return true;
    return false;
}

/*  Author: Ho Yuet
 * Write for saving
 */
void StreetCard::write(QJsonObject &json) const
{
    PropertyCard::write(json);

    json["numberHouses"] = numberHouses;
    json["hasHotel"] = hasHotel;
    json["hasSkyscraper"] = hasSkyscraper;
    json["buildingPrice"] = buildingPrice;
    json["priceRentOneHouse"] = priceRentOneHouse;
    json["priceRentTwoHouse"] = priceRentTwoHouse;
    json["priceRentThreeHouse"] = priceRentThreeHouse;
    json["priceRentFourHouse"] = priceRentFourHouse;
    json["priceRentWithHotel"] = priceRentWithHotel;
    json["priceRentWithSkyscraper"] = priceRentWithSkyscraper;

}

/*  Author: Ho Yuet
 * Read for loading
 */
void StreetCard::read(const QJsonObject &json)
{
    PropertyCard::read(json);

    numberHouses = json["numberHouses"].toInt();
    hasHotel = json["hasHotel"].toBool();
    hasSkyscraper = json["hasSkyscraper"].toBool();
    buildingPrice = json["buildingPrice"].toInt();
    priceRentOneHouse = json["priceRentOneHouse"].toInt();
    priceRentTwoHouse = json["priceRentTwoHouse"].toInt();
    priceRentThreeHouse = json["priceRentThreeHouse"].toInt();
    priceRentFourHouse = json["priceRentFourHouse"].toInt();
    priceRentWithHotel = json["priceRentWithHotel"].toInt();
    priceRentWithSkyscraper = json["priceRentWithSkyscraper"].toInt();

}


