#include "propertycard.h"
#include <QColor>
#include <QJsonObject>
#include <QDebug>

PropertyCard::PropertyCard()
{

}

PropertyCard::PropertyCard(QString newName,QColor newColour, int newValue, int newRent, int newMortgage)
{
    value = newValue;
    name = newName;
    priceMortgage = newMortgage;
    priceRent = newRent;
    colour = newColour;
    isMortgaged = false;
}

QString PropertyCard::getName()
{
    return name;
}

int PropertyCard::getValue()
{
    return value;
}

int PropertyCard::getPriceRent()
{
    return priceRent;
}

int PropertyCard::getPriceMortgage()
{
    return priceMortgage;
}

/*
 * returns true if property is mortgaged
 */
bool PropertyCard::checkIfMortgaged()
{
    return isMortgaged;
}

/*
 * switches the isMortgaged to false if it was true and vice versa
 */
void PropertyCard::switchMortgaged()
{
    if (isMortgaged)
        isMortgaged = false;
    else
        isMortgaged = true;
}

/*
 * Returns the colour
 */
QColor PropertyCard::getColour()
{
    return colour;
}

/*
 * Returns the type of the card
 */
PropertyCard::PropertyType PropertyCard::getType()
{
    return type;
}

/*
 * save
 */
void PropertyCard::write(QJsonObject &json) const
{
    json["value"] = value;
    json["colourR"] = colour.red();
    json["colourG"] = colour.green();
    json["colourB"] = colour.blue();
    json["name"] = name;
    json["priceRent"] = priceRent;
    json["priceMortgage"] = priceMortgage;
    json["isMortgaged"] = isMortgaged;
    json["type"] = type;
}

/*
 * load
 */
void PropertyCard::read(const QJsonObject &json)
{
    value = json["value"].toInt();
    int red = json["colourR"].toInt();
    int green = json["colourG"].toInt();
    int blue = json["colourB"].toInt();
    colour = QColor(red,green,blue);
    name = json["name"].toString();
    priceRent = json["priceRent"].toInt();
    priceMortgage = json["priceMortgage"].toInt();
    isMortgaged = json["isMortgaged"].toBool();
    type = PropertyType (qRound(json["type"].toDouble()));
}


