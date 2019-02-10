// Author: Sebastiaan
#ifndef PLAYER_H
#define PLAYER_H


#include <QColor>
#include <QList>
#include <QObject>

class Card;
class Dice;
class Board;
class Player;
class PropertyCard;
class BusCard;

class Player : public QObject
{
    Q_OBJECT
public:
    Player();
    Player(const QColor col, const int mon, const int numPlayer);
    Card* takeCard(Board& board)const;
    void changeMoney(int amount);   // adds or substracts the amount money
    void move(int newPosition); // move to new position
    int getCurrentPosition();
    void takeBusTicket(BusCard* busTicket);
    bool hasBusTickets();
    void buyCard(PropertyCard* card, int amount = 0); // buys the given card
    void addPropertyCard(PropertyCard* card);
    int getNumberPlayer()const;  // returns the number the player is
    QList<PropertyCard*> getProperties()const;   // returns the players properties
    void sellCard(PropertyCard* card);
    void mortgageProperty(PropertyCard* card);
    PropertyCard* getPropertyCard(QString name);
    QColor getColour();
    bool checkColourInProperty(QColor cardColour)const;
    int getNumberOfColorProperties(QColor color)const;
    bool checkTransaction(int amount);
    void putInJail();
    void getOutJail();
    void addRoll(QList<Dice*> lastRoll);
    bool checkDoublesTwice();
    bool isInJail();
    void rollInJail();
    bool hasRolledThreeTimes();
    void addJailCard();
    bool hasJailCard();
    void useJailCard();
    bool checkIfColourMortgaged(QColor propertyColour);
    void write(QJsonObject &json)const; // load
    void read(const QJsonObject &json);// save
    void removePropertyCard(PropertyCard *cardToRemove);
    void setPlayerNumber(int newNumber);
public slots:
    void getMortgage();
signals:
    PropertyCard* askMortgage();
    void moved(int currentPlayer, int position);   // send new position to View
    void moneyChanged(int amount);
    void notEnoughMoney();
    void broke(int numberPlayer);
private:
    QColor colour;
    QList<PropertyCard*> propertyCards;
    QList<BusCard*> busTickets;
    QList<QList<Dice*>> lastRolls;
    int money;
    int numberPlayer;
    int currentPosition;
    bool inJail;
    int timesRolledInJail;
    int amountOfJailCards;
    bool checkIfBroke(int amount);
    void instantiateWhichCard(const QJsonObject &json); // instantiates cards correctly
    void clearLastRolls();
    Dice* instantiateWhichDice(const QJsonObject &json);

};

#endif // PLAYER_H
