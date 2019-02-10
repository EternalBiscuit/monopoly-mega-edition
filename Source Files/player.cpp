// Author: Sebastiaan
#include "player.h"
#include "board.h"
#include "propertycard.h"
#include "companycard.h"
#include "streetcard.h"
#include "railroadcard.h"
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>

Player::Player()
{
    money = 0;
    numberPlayer = 0;
    currentPosition = 0;
    amountOfJailCards = 0;
    timesRolledInJail= 0;
}

/*  Author: Sebastiaan
 *  Constructor of Player
 *  3 arguments: colour, starting money, number of player
 */
Player::Player(const QColor col, const int mon, const int numPlayer)
{
    colour = col;
    money = mon;
    numberPlayer = numPlayer;
    currentPosition = 0;
    inJail = false;
    amountOfJailCards = 0;
    timesRolledInJail = 0;
}

void Player::getMortgage()
{

}

/*  Author: Ho Yuet
 *  Removes the given PropertyCard
 */
void Player::removePropertyCard(PropertyCard *cardToRemove)
{
    for (int i = 0; i < propertyCards.count(); i++)
    {
        // if found
        if(propertyCards[i]->getName() == cardToRemove->getName())
        {
            propertyCards.removeAt(i);
            return;
        }
    }
}

void Player::setPlayerNumber(int newNumber)
{
    numberPlayer = newNumber;
}


bool Player::checkIfBroke(int amount)
{
    int totalBalance = 0;

    foreach(PropertyCard* property, propertyCards)
    {
        totalBalance+= property->getPriceMortgage()/2;
        totalBalance+= property->getNumberHouses()*(property->getBuildingPrice()/2);
    }

    totalBalance += money;

    if (totalBalance < amount)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/* Author: Sebastiaan
 * Debits or credits the amount of money
 * 1 argument: amount of money
 */
void Player::changeMoney(int amount)
{
    if (amount >= 0 || money >= amount)  // if adding money or enough money
    {
        money += amount;
        emit moneyChanged(money);
    }
    else if (checkIfBroke(amount))
    {
        emit broke(numberPlayer);
    }
    else if (money < amount)
    {
        emit notEnoughMoney();
    }

}

/*  Author: Ho Yuet
 * Checks if one of the property is mortgaged with the given colour
 */
bool Player::checkIfColourMortgaged(QColor propertyColour)
{
    foreach(PropertyCard* card, propertyCards)
    {
        if (card->getColour() == propertyColour && card->checkIfMortgaged())
            return true;
    }
    return false;
}

/*  Author: Ho Yuet
 *  Moves the player from the old position to the new position
 * 1 argument: new position
 */
void Player::move(int newPosition)
{

    emit moved(numberPlayer, newPosition);
    currentPosition = newPosition;
}

int Player::getCurrentPosition()
{
    return currentPosition;
}

void Player::takeBusTicket(BusCard* busTicket)
{
    busTickets.append(busTicket);
}

bool Player::hasBusTickets()
{
    return !(busTickets.isEmpty());
}

int Player::getNumberPlayer()const
{
    return numberPlayer;
}

/* Author: Ho Yuet
 * returns the properties of the player
 */
QList<PropertyCard *> Player::getProperties()const
{
    return propertyCards;
}


void Player::sellCard(PropertyCard *card)
{
    if (card != NULL)
    {

    }
}

/*  Author: Ho Yuet
 *  Mortgages the given property
 */
void Player::mortgageProperty(PropertyCard *card)
{
    if (card == NULL)
        return;
    int mortgageValue = card->getPriceMortgage();

}

PropertyCard *Player::getPropertyCard(QString name)
{
    foreach(PropertyCard* card, propertyCards)
    {
        if (card->getName() == name)
            return card;
    }
    return NULL;
}

QColor Player::getColour()
{
    return colour;
}

/* Author: Ho Yuet
 * checks if the colour is in de properties
 * returns true if it is, false otherwise
 */
bool Player::checkColourInProperty(QColor cardColour)const
{
    foreach(PropertyCard* card, propertyCards)
    {
        if (card->getColour() == cardColour)
            return true;
    }
    return false;
}

int Player::getNumberOfColorProperties(QColor color) const
{
    int numberOfColorProperties = 1;
    foreach(PropertyCard* prop, propertyCards)
    {
        if (prop->getColour() == color)
        {
            numberOfColorProperties++;
        }
    }

    return numberOfColorProperties;

}

bool Player::checkTransaction(int amount)
{
    if (amount > money)
    {
        return false;
    }

    return true;
}

void Player::putInJail()
{
    inJail = true;
}

void Player::getOutJail()
{
    inJail = false;
    timesRolledInJail = 0;
    lastRolls.clear();
}

void Player::addRoll(QList<Dice *> lastRoll)
{
    lastRolls.append(lastRoll);

    if (lastRolls.count() > 2)
    {
        lastRolls.removeFirst();
    }
}

bool Player::checkDoublesTwice()
{
    int timesDouble = 0;

    if (lastRolls.count() > 1)
    {
        foreach (QList<Dice*> roll, lastRolls)
        {
            if (roll[0]->getRolledSymbol().toInt() == roll[1]->getRolledSymbol().toInt())
            {
                timesDouble++;
            }
        }
    }

    if (timesDouble > 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Player::isInJail()
{
    return inJail;
}

void Player::rollInJail()
{
    timesRolledInJail++;
}

bool Player::hasRolledThreeTimes()
{
    if (timesRolledInJail >= 3)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Player::addJailCard()
{
    amountOfJailCards++;
}

bool Player::hasJailCard()
{
    if (amountOfJailCards > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Player::useJailCard()
{
    amountOfJailCards--;
}


/*
 * Buys a given PropertyCard
 */
void Player::buyCard(PropertyCard *card, int amount)
{
    propertyCards.append(card);

    if (amount > 0)
    {
        changeMoney(-amount);
    }
    else
    {
        changeMoney(-(card->getValue()));
    }
}

void Player::addPropertyCard(PropertyCard *card)
{
    this->propertyCards.append(card);
}


Card* Player::takeCard(Board& board) const
{
    Card* card;
    return card;
}

/*
 * Save
 */
void Player::write(QJsonObject &json) const
{
    json["isJail"] = inJail;
    json["colourR"] = colour.red();
    json["colourG"] = colour.green();
    json["colourB"] = colour.blue();
    json["amountOfJailCards"] = amountOfJailCards;

    QJsonArray propertyCardsArray;
    foreach(const PropertyCard* card, propertyCards)
    {
        QJsonObject cardObject;
        card->write(cardObject);
        propertyCardsArray.append(cardObject);
    }
    json["propertyCards"] = propertyCardsArray;
    //busCards
    // dice rolls
    QJsonArray lastRollsArray;
    foreach(const QList<Dice*> rolls, lastRolls)
    {
        QJsonArray rollsArray;
        foreach(Dice* roll, rolls)
        {
            QJsonObject diceObject;
            roll->write(diceObject);
            rollsArray.append(diceObject);
        }
        lastRollsArray.append(rollsArray);
    }
    json["lastRolls"] = lastRollsArray;

    json["money"] = money;
    json["numberPlayer"] = numberPlayer;
    json["currentPosition"] = currentPosition;
    json["timesRolledInJail"] = timesRolledInJail;
}


/*
 * Load
 */
void Player::read(const QJsonObject &json)
{
    if (!propertyCards.isEmpty())
        propertyCards.clear();
    QJsonArray propertyCardsArray = json["propertyCards"].toArray();
    for(int i =0; i < propertyCardsArray.size(); i++)
    {
        QJsonObject cardObject = propertyCardsArray[i].toObject();
        instantiateWhichCard(cardObject);

    }
    int red = json["colourR"].toInt();
    int green = json["colourG"].toInt();
    int blue = json["colourB"].toInt();
    colour = QColor(red,green,blue);
    qDebug() << colour;
    //bus
    //dice

    /*clearLastRolls();
    QJsonArray lastRollsArray = json["lastRolls"].toArray();
    for(int i =0; i < lastRollsArray.size(); i++)
    {
        QList<Dice*> dices;
        QJsonArray rollsArray = lastRollsArray[i].toArray();
        for (int j = 0; rollsArray.size(); j++)
        {
            QJsonObject diceObject = rollsArray[j].toObject();
            dices.append(instantiateWhichDice(diceObject));
        }
        lastRolls.append(dices);
    }
*/
    money = json["money"].toInt();
    numberPlayer = json["numberPlayer"].toInt();
    currentPosition = json["currentPosition"].toInt();
    amountOfJailCards = json["amountOfJailCards"].toInt();
    inJail = json["inJail"].toBool();
    timesRolledInJail = json["timesRolledInJail"].toInt();
}

/*  Author: Ho Yuet
 * Instatiates the correct PropertyCard after loading
 */
void Player::instantiateWhichCard(const QJsonObject &json)
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

/*  Author: Ho Yuet
 *  Deletes all last rolls
 */
void Player::clearLastRolls()
{
    for(int i = 0; i< lastRolls.size(); i++)
    {
        for(int j =0; j> lastRolls[i].size(); j++)
        {
            delete lastRolls[i][j];
        }
    }
}

/*  Author: Ho Yuet
 * instantiates the correct dice (normal or speed
 */
Dice* Player::instantiateWhichDice(const QJsonObject &json)
{
    switch (Dice::TypeDice(qRound(json["type"].toDouble()))) {
    case Dice::TypeDice::DICE:  // normal dice
    {
        Dice* dice = new Dice;
        dice->read(json);
        return dice;
        break;
    }
    case Dice::TypeDice::SPEEDDICE:     // speed dice
    {
        SpeedDice* dice = new SpeedDice;
        dice->read(json);
        return dice;
        break;
    }
    default:
        break;
    }
    return NULL;

}


