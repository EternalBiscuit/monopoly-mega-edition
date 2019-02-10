#ifndef COMPANYCARD_H
#define COMPANYCARD_H
#include "propertycard.h"

class CompanyCard: public PropertyCard
{
    Q_OBJECT
public:
    CompanyCard();
    CompanyCard(QString newName, QColor newColour,int newValue, int newRent, int newMortgage);
    int getRent(int number = 0, int pips = 0)const;
    //int getRent(int numberUtilities)const;
    void useCard();
    int getAmountBuildableBuildings();
    int getBuildingPrice();
    bool canBuildBuildings(bool hasMonopoly);
    void buildBuilding();
    int getAmountBuildings();
    int getNumberHotels();
    int getNumberHouses();
    void removeAllBuildings();
void removeBuilding();
    bool canRemoveBuilding();
    PropertyCard::TypeBuilding getTypeBuilding();

};

#endif // COMPANYCARD_H
