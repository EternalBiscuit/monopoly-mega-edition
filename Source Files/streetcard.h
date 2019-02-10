#ifndef STREETCARD_H
#define STREETCARD_H
#include "propertycard.h"

class StreetCard: public PropertyCard
{
    Q_OBJECT
public:
    StreetCard();
    StreetCard(QString newName,QColor newColour, int newValue, int newRent, int newMortgage, int newBuildingPrice, int oneHousePrice, int twoHousePrice, int threeHousePrice, int fourHousePrice, int oneHotelPrice, int oneSkyPrice);
    void buildHouse();
    void buildHotel();
    void buildSkyscraper();
    int getRent(int number = 0, int pips = 0)const;
    void useCard();
    // getters
    int getBuildingPrice();
    int getOneHouseRentPrice();
    int getTwoHouseRentPrice();
    int getThreeHouseRentPrice();
    int getFourHouseRentPrice();
    int getHotelRent();
    int getSkyscraperRent();
    int getAmountBuildableBuildings();
    bool canBuildBuildings(bool hasMonopoly);   // checks if the card can build buildings
    void buildBuilding();   // builds a building
    int getAmountBuildings();   // get the amount of buildings it has
    int getNumberHotels();
    int getNumberHouses();
    void removeAllBuildings();
    PropertyCard::TypeBuilding getTypeBuilding();
    void removeBuilding();
    bool canRemoveBuilding();

    void write(QJsonObject &json)const;
    void read(const QJsonObject &json);

private:
    int numberHouses;
    bool hasHotel;
    bool hasSkyscraper;
    int buildingPrice;
    int priceRentOneHouse;
    int priceRentTwoHouse;
    int priceRentThreeHouse;
    int priceRentFourHouse;
    int priceRentWithHotel;
    int priceRentWithSkyscraper;
    static const int MAXHOTELS = 1;
    static const int MAXSKYSCRAPERS = 1;
    static const int MAX_AMOUNT_HOUSES = 4;




};

#endif // STREETCARD_H
