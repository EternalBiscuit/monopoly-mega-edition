#include "propertyspace.h"
#include <QJsonObject>

PropertySpace::PropertySpace()
{

}

PropertySpace::PropertySpace(int newPrice, QString newName, QColor newColour)
{
    name = newName;
    price = newPrice;
    colour = newColour;
    isOwned = false;
    owner = -1;
}

int PropertySpace::getOwner()
{
    return owner;
}

/*
 * Checks if the space is owned
 * returns true if it's owned, false otherwise
 */
bool PropertySpace::checkIfOwned()
{
    return isOwned;
}

/*
 * Returns the name of the Property
 */
QString PropertySpace::getName()
{
    return name;
}

void PropertySpace::hasOwnership()
{
    isOwned = true;
}

void PropertySpace::newOwner(int ownerNumber)
{
    owner = ownerNumber;
}

/*  Author: Ho Yuet
 *  load
 */
void PropertySpace::read(const QJsonObject &json)
{
    type = Type(qRound(json["type"].toDouble()));
    name = json["name"].toString();
    int red = json["colourR"].toInt();
    int green = json["colourG"].toInt();
    int blue = json["colourB"].toInt();
    colour = QColor(red,green,blue);
    owner = json["owner"].toInt();
    isOwned = json["isOwned"].toBool();


}

/*  Author: Ho Yuet
 * save
 */
void PropertySpace::write(QJsonObject &json) const
{
    json["type"] = type;
    json["price"] = price;
    json["name"] = name;
    json["colourR"] = colour.red();
    json["colourG"] = colour.green();
    json["colourB"] = colour.blue();
    json["owner"] = owner;
    json["isOwned"] = isOwned;
}



