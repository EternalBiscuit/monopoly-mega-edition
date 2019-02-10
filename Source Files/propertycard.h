#ifndef PROPERTYCARD_H
#define PROPERTYCARD_H
#include "card.h"
#include <QColor>

class PropertyCard: public Card
{
    Q_OBJECT
public:
    enum TypeBuilding{HOUSE,HOTEL,SKYSCRAPER,RAILDEPOT, NONE};
    enum PropertyType{STREET, COMPANY, STATION};
    PropertyCard();
    PropertyCard(QString newName,QColor newColour, int newValue, int newRent, int newMortgage);
    virtual int getRent(int number = 0, int pips = 0)const = 0;
    virtual void useCard()= 0;
    QString getName();
    int getValue();
    int getPriceRent();
    int getPriceMortgage(); // get the price of the mortgage value
    bool checkIfMortgaged();    // checks if it's mortgages
    void switchMortgaged(); // changes the mortgage
    QColor getColour(); // get the colour of the card
    PropertyType getType();
    virtual int getAmountBuildableBuildings() = 0;
    virtual int getBuildingPrice() = 0;
    virtual bool canBuildBuildings(bool hasMonopoly) = 0;
    virtual void buildBuilding() = 0;
    virtual int getAmountBuildings() = 0;
    virtual int getNumberHouses() = 0;
    virtual int getNumberHotels() = 0;
    virtual void removeAllBuildings() = 0;
    virtual bool canRemoveBuilding() = 0;
    virtual void removeBuilding() = 0;
    virtual PropertyCard::TypeBuilding getTypeBuilding() = 0;
    virtual void write(QJsonObject &json)const;
    virtual void read(const QJsonObject &json);
protected:
    int value;
    QColor colour;
    QString name;
    int priceRent;
    int priceMortgage;
    bool isMortgaged;
    PropertyType type;

};


#endif // PROPERTYCARD_H
