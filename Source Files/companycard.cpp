#include "companycard.h"

CompanyCard::CompanyCard()
{

}

CompanyCard::CompanyCard(QString newName,QColor newColour, int newValue, int newRent, int newMortgage)
    :PropertyCard(newName, newColour, newValue, newRent, newMortgage)
{
    type = PropertyCard::PropertyType::COMPANY;
}

int CompanyCard::getRent(int number, int pips) const
{

    switch (number) {
    case 1:
        return priceRent*pips*4;
        break;
    case 2:
        return priceRent*pips*10;
    case 3:
        return priceRent*pips*20;
    }
}

void CompanyCard::useCard()
{

}

/*
 * Gets the amount of buildings a company can build (always 0)
 */
int CompanyCard::getAmountBuildableBuildings()
{
    return 0;
}

int CompanyCard::getBuildingPrice()
{
    return 0;
}

/*  Author: Ho Yuet
 * Checks if you can build a building
 * always return false
 */
bool CompanyCard::canBuildBuildings(bool hasMonopoly)
{
    return false;
}

void CompanyCard::buildBuilding()
{
    return;
}

int CompanyCard::getAmountBuildings()
{
    return 0;
}

int CompanyCard::getNumberHotels()
{
    return 0;
}

int CompanyCard::getNumberHouses()
{
    return 0;
}

void CompanyCard::removeAllBuildings()
{
    return;
}

void CompanyCard::removeBuilding()
{
    return;
}

bool CompanyCard::canRemoveBuilding()
{
    return false;
}

PropertyCard::TypeBuilding CompanyCard::getTypeBuilding()
{
    return NONE;
}

