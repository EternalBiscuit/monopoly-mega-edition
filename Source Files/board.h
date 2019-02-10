// Author: Ho Yuet
#ifndef BOARD_H
#define BOARD_H
#include <QObject>
#include "dice.h"
#include "speeddice.h"
#include"dicedialog.h"
#include "space.h"
#include "propertycard.h"

class Space;
class ChanceCard;
class CommunityChestCard;
class BusCard;
class Player;
class Dice;
class Bank;
class PropertyCard;

class Board: public QObject
{
    Q_OBJECT
public:
	enum TypeTransaction{BUY, SELL};
    Board(int numPlayers);
    QList<Player *> getPlayers();
    enum TypeBuildings{HOUSE,HOTEL,SKYSCRAPER,RAILDEPOT};
    QList<Space *> getSpaces();
    PropertyCard* getBankPropertyCard(QString name);
    int getNumberOfPlayerCards(const Player& player, QColor colour)const;//counts how many cards a player has with the given colour
    int getPips()const;// gets the pips of a dice
    bool checkHasFullMonopoly(const Player& player, QColor colour)const; // checks if a given player has a full monopoly in a given colour
    bool checkHasMajority(const Player& player, QColor colour)const;    //checks if a given player has a majority with a given coluor
    void goToJail();//puts current player in jail
    void goToStart(); //moves the current player to start
    QList<PropertyCard*> getBankPropertyCards()const;
    int getIndexSpaceFromPropertyName(QString propertyName);    // searches in what index the space is with the given property name
    CommunityChestCard *getRandomCommChestCard();
    QList<CommunityChestCard*> getCommunityChestCards();
    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;

private:
    static const int SIZE_OF_BOARD = 52;
    static const int MAXBUSTICKETS = 16;
    static const int SIZE_OF_SIDE = 13;
    static const int NUMBER_OF_DICES = 3;
    QList<Space*> spaces;
//    QList<ChanceCard*> chanceCards;
    QList<CommunityChestCard*> communityChestCards;
    QList<Player*> players;
    Bank* bank;
    QList<Dice*>dices;
    QList<BusCard*> bustickets;
    int currentTurn;
    void movePlayer(int numberSpaces);  // moves the player n amount of spaces
    void insertSpaces();    // read spaces from a file and creates it
    void insertCommunityCards();
    QColor getColorFromString(QString color);   // convert a colour in string into QColor
    void rollDices();   // rolls the dices
    int getNumberOfColourCards(QColor colour)const; // counts how many cards there are with the same given colour 
    bool checkColourAlreadyInCards(const QList<PropertyCard*> cards, QColor colour)const; // checks if the given colour is already in de list of cards
    void checkStart(int oldPos, int newPos);
    bool checkDoublesThrice();
    void diceMoveOutOfJail();
    void finishTurn(int numberSpaces);
    int findSpace(Space::Type type)const;
    void reloadSpaces();
    void instantiateWhichSpace(const QJsonObject &json);
    void reloadBuildings();

public slots:
    void switchTurn();      // switch turn to next player
    void addBusTicket();    // adds a bus ticket to the current player
    void moveToChance();    // moves to the nearest chance space
    void moveToUnownedProperty();   // moves to the nearest unowned property if possible
    void calculateBusSelection();   //calculates the distance for using the bus ticket
    void takeBus(int newPos);   // uses the bus ticket function
    void doDiceMove();  // does the dice functions
    void buyProperty(); // buys the property the current player stands on
    void mortgageProperty(const QString name);  // (un)mortgages the property
    void checkBuildingBuyable();    // checks if the building the player is standing on is buyable
    void getMaxAmountBuildableBuilding(QColor colour); // gets the max amount of buildable buildings of a given colour
    void buildBuildings(QColor colour, int amount); // builds the amount of building on a colour
    int getCurrentTurn()const;
    void doTransaction(int amount);
    void completeAuction(int player, int amount, int spaceIndex);
    void checkBid(int player, int amount);
    void inJailPay();
    void inJailRoll();
    void inJailUseCard();
    void retirePlayer();
    void givePossibleTradeProperty(int askingPlayer, int vendorPlayer, const QString name);  // sells the property with a given name

    void sellBuildings(QColor colour, int amount);
    void checkBuildingsSellable();
    void getMaxAmountSellableBuilding(QColor colour); // gets the max amount of buildable buildings of a given colour
    void trade(int askingPlayer, QList<QString> toGiveProperties, int toPlayer, QString askedPropertyName, int amountMoney);
signals:
    void rolled(const QString firstDiceValue, const QString secondDiceValue, const QString thirdDiceValue);
    void turnSwitched(int currentTurn); // notify view turn has switched
    void busTicketDone(int succes);
    void hasBusTickets();
    void busSelectionCalculated(int currentPos, int endPos);
    void busRolled();
    void payRent(int rent);
    void buildingsAreBuyable(QList<PropertyCard*>cards, Board::TypeTransaction transaction);
    void boughtProperty(int player, QColor colour,int space);
    void startAuction(int players);
    void bidChecked(bool bidOK);
    void passedStart();
    void giveAmountBuildableBuildings(int amount);
    void buildingsAreBuilded(int indexPosition, PropertyCard::TypeBuilding building, int amount);
    void movedToJail();
    void isInJail(bool hasJailCard);
    void inJailRolled(bool succes, int firstDice, int secondDice);
    void inJailPaid();
    void inJailCardUsed();
    void rolledTriple();
    void rolledDouble();
    void unableToBuildBuildings();
    void unableToMortgage();
    void buildingsAreSellable(QList<PropertyCard*>cards, Board::TypeTransaction transaction);
    void giveAmountSellableBuildings(int amountBuildings);
    void reload(int numberPlayers);
    void negotiate(int askingPlayer, QList<PropertyCard*> properties, int vendorPlayer, QString forProperty);

};

#endif // BOARD_H



