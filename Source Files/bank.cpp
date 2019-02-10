#include "bank.h"
#include "streetcard.h"
#include "railroadcard.h"
#include "companycard.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QColor>
#include <QStringList>
#include <QJsonArray>
#include <QJsonObject>


Bank::Bank()
{
    readStreetCardsFromFile();
    readCompanyCardsFromFile();
    readRailCardsFromFile();
}

void Bank::giveMoney(Player &player)
{

}

/* Author: Ho Yuet
 * Removes a given card from the bank
 */
void Bank::removeProperty(QString nameProperty)
{
    for(int i =0; i < propertyCards.count(); i++)
    {
        if (propertyCards[i]->getName() == nameProperty)    // if card is found
        {
            propertyCards.removeAt(i);
            return;
        }
    }
}

/* Author: Ho Yuet
 * Adds the propertycard back to the banks propertyCards
 */
void Bank::addProperty(PropertyCard &card)
{
    propertyCards.append(&card);
}

/* Author: Ho Yuet
 * Gets a card derived from a name
 * Returns NULL if the card is not found
 */
PropertyCard *Bank::getCard(QString cardName)
{
    for(int i =0; i < propertyCards.count(); i++)
    {
        if (propertyCards[i]->getName() == cardName)    // if card is found
            return propertyCards[i];
    }
    return NULL;
}

bool Bank::foundColourInBank(QColor colour)
{
    foreach(PropertyCard* card, propertyCards)
    {
        if (card->getColour() == colour)    // if the colour is found in bank
            return true;
    }
    return false;
}

int Bank::getNumberOfColourCards(QColor colour)
{
    int numberOfColourCards = 0;

    foreach (PropertyCard* card, propertyCards)
    {
        if (card->getColour() == colour)
        {
            numberOfColourCards++;
        }
    }

    return numberOfColourCards;
}

QList<PropertyCard *> Bank::getCards()
{
    return propertyCards;
}

/* Author: Ho Yuet
 * Reads all street cards from a file
 */
void Bank::readStreetCardsFromFile()
{
    QFile streetFile("../MonopolyStreetCards.txt");  // file is outside of the projectfile
    QStringList streetInfo;

    if (!streetFile.exists())
    {
        qDebug() << "MonopolyStreetCards file does not exist";
        return;
    }
    if (!streetFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Can't open MonopolyStreetCards file";
        return;
    }

    QTextStream in(&streetFile);
    while (!in.atEnd())
    {
        QString line = in.readLine();   // read line by line
        streetInfo = line.split(",");    // split line by ,

        //add streets
        if(!streetInfo[0].contains("*") && streetInfo[0] != "")
            propertyCards.append(new StreetCard(streetInfo[0], getColorFromString(streetInfo[1]), streetInfo[2].toInt(), streetInfo[3].toInt(),streetInfo[4].toInt(),streetInfo[5].toInt(),streetInfo[6].toInt(),
                    streetInfo[7].toInt(),streetInfo[8].toInt(),streetInfo[9].toInt(),streetInfo[10].toInt(),streetInfo[11].toInt()));
    }
    streetFile.close();
}

/* Author: Ho Yuet
 * Reads all Company cards from a file
 */
void Bank::readCompanyCardsFromFile()
{
    QFile companyFile("../MonopolyCompanyCards.txt");  // file is outside of the projectfile
    QStringList companyInfo;

    if (!companyFile.exists())
    {
        qDebug() << "MonopolyCompanyCards file does not exist";
        return;
    }
    if (!companyFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Can't open MonopolyCompanyCards file";
        return;
    }

    QTextStream in(&companyFile);
    while (!in.atEnd())
    {
        QString line = in.readLine();   // read line by line
        companyInfo = line.split(",");    // split line by ,

        //add streets
        if(!companyInfo[0].contains("*") && companyInfo[0] != "")
            propertyCards.append(new CompanyCard(companyInfo[0], getColorFromString(companyInfo[1]), companyInfo[2].toInt(), companyInfo[3].toInt(),companyInfo[4].toInt()));
    }
    companyFile.close();
}

/* Author: Ho Yuet
 * Reads all Rail road cards from a file
 */
void Bank::readRailCardsFromFile()
{
    QFile railFile("../MonopolyRailCards.txt");  // file is outside of the projectfile
    QStringList railInfo;

    if (!railFile.exists())
    {
        qDebug() << "MonopolyRailCards file does not exist";
        return;
    }
    if (!railFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Can't open MonopolyRailCards file";
        return;
    }

    QTextStream in(&railFile);
    while (!in.atEnd())
    {
        QString line = in.readLine();   // read line by line
        railInfo = line.split(",");    // split line by ,

        //add streets
        if(!railInfo[0].contains("*") && railInfo[0] != "")
            propertyCards.append(new RailRoadCard(railInfo[0], getColorFromString(railInfo[1]), railInfo[2].toInt(), railInfo[3].toInt(),railInfo[4].toInt(), railInfo[5].toInt()));
    }
    railFile.close();
}

/*Author: Ho Yuet
 * Converts a string color to a QColor
 * 1 argument: color in QString
 */
QColor Bank::getColorFromString(QString color)
{
    if (color == "Red")
        return QColor(255,0,0);
    if (color == "Brown")
        return QColor(139,69,19);
    if (color == "Cyan")
        return QColor(0,255,255);
    if (color == "Black")
        return QColor(0,0,0);
    if (color == "Pink")
        return QColor(255,0,255);
    if (color == "Grey")
        return QColor(128,128,128);
    if (color == "Orange")
        return QColor(255,165,0);
    if (color == "Yellow")
        return QColor(255,255,0);
    if (color == "Green")
        return QColor(0,255,0);
    if (color == "Blue")
        return QColor(0,0,255);

    return QColor(255,255,255);
}

/*  Author: Ho Yuet
 * load
 */
void Bank::read(const QJsonObject &json)
{
    for(int i = 0; i < propertyCards.size();i++)
    {
        delete propertyCards[i];
    }
    if (!propertyCards.isEmpty())
        propertyCards.clear();
    QJsonArray cardsArray = json["propertyCards"].toArray();
    for (int i = 0; i < cardsArray.size();i++)
    {
        QJsonObject cardObject = cardsArray[i].toObject();
        instantiateWhichCard(cardObject);
    }

}

/* Author: Ho Yuet
 * Save
 */
void Bank::write(QJsonObject &json) const
{
    //bus
    QJsonArray propertyCardsArray;
    foreach(const PropertyCard* card, propertyCards)
    {
        QJsonObject cardObject;
        card->write(cardObject);
        propertyCardsArray.append(cardObject);
    }
    json["propertyCards"] = propertyCardsArray;

}

/*  Author: Ho Yuet
 * Instatiates the correct PropertyCard after loading
 */
void Bank::instantiateWhichCard(const QJsonObject &json)
{
    switch (PropertyCard::PropertyType(qRound(json["type"].toDouble()))) {
    case PropertyCard::PropertyType::COMPANY:
    {
        CompanyCard* card = new CompanyCard;
        card->read(json);
        propertyCards.append(card);
        break;
    }
    case PropertyCard::PropertyType::STATION:
    {
        RailRoadCard* card = new RailRoadCard;
        card->read(json);
        propertyCards.append(card);
        break;
    }
    case PropertyCard::PropertyType::STREET:
    {
        StreetCard* card = new StreetCard;
        card->read(json);
        propertyCards.append(card);
        break;
    }
    default:
        break;
    }
}





