#include "board.h"
#include "space.h"
#include "player.h"
#include "startspace.h"
#include "busspace.h"
#include "chancespace.h"
#include "communitychestspace.h"
#include "companyspace.h"
#include "gotojailspace.h"
#include "parkingspace.h"
#include "streetspace.h"
#include "jailspace.h"
#include "streetcard.h"
#include "auctionspace.h"
#include "stationspace.h"
#include "buscard.h"
#include "bank.h"
#include "railroadcard.h"
#include "companycard.h"
#include "propertycard.h"
#include "moneyallcommunitycard.h"
#include "moneycommunitycard.h"
#include "moneypropcommunitycard.h"
#include "togocommunitycard.h"
#include "tojailcommunitycard.h"
#include "outofjailcommunitycard.h"
#include <QDebug>
#include <QFile>
#include <QCoreApplication>
#include <QList>
#include <QFileInfo>
#include <QJsonArray>
#include <QJsonObject>


/*  Author: Sebastiaan
 *  Constructor of Board
 * Arguments: number of players
 */
Board::Board(int numPlayers)
{
    dices.append(new Dice());
    dices.append(new Dice());
    dices.append(new SpeedDice());
    insertSpaces();
    insertCommunityCards();

    // player begins at 0
    for (int i = 0; i < numPlayers; i++)
    {
        players.append(new Player(QColor::fromHsl(i*45, 255, 150), 2500, i));
    }
    currentTurn = 0;
    bank = new Bank;
    for (int i = 0; i < MAXBUSTICKETS; i++)
    {
        bustickets.append(new BusCard());
    }

}

/*  Author: Ho Yuet
 * Sells the given property of the current player to the bank
 *
 */
void Board::givePossibleTradeProperty(int askingPlayer, int vendorPlayer,const QString name)
{
    emit negotiate(askingPlayer, players[askingPlayer]->getProperties(), vendorPlayer, name);
}


/*  Author: Ho Yuet
 *  trade the properties (QString) and a sum of money from askingPlayer, to toPlayer with a askedProperty
 */
void Board::trade(int askingPlayer, QList<QString> toGiveProperties, int toPlayer, QString askedPropertyName, int amountMoney)
{
    Player* givePlayer = players[askingPlayer];
    Player* recievePlayer = players[toPlayer];
    int onSpaceIndex = 0;
    PropertyCard* card = NULL;
    // gave player
    foreach(QString cardName, toGiveProperties) // give the properties to recievePlayer
    {
        card = givePlayer->getPropertyCard(cardName);
        if (card->checkIfMortgaged())   // if the card is mortgaged, pay additional fee
        {
            recievePlayer->changeMoney(-((int)(card->getPriceMortgage() * 1.1)));
        }
        givePlayer->removePropertyCard(card);
        recievePlayer->buyCard(card);

        onSpaceIndex = getIndexSpaceFromPropertyName(cardName);
        PropertySpace* propertySpace = (PropertySpace*)spaces[onSpaceIndex];
        propertySpace->newOwner(toPlayer);

        emit boughtProperty(toPlayer,recievePlayer->getColour(),onSpaceIndex);
    }
    // recieved player
    // give the property (askedPropertyName) to givePlayer
    card = recievePlayer->getPropertyCard(askedPropertyName);
    givePlayer->buyCard(card, amountMoney); // gets the card
    recievePlayer->removePropertyCard(card);    // remove the card
    recievePlayer->changeMoney(amountMoney);
    onSpaceIndex = getIndexSpaceFromPropertyName(askedPropertyName);
    PropertySpace* propertySpace = (PropertySpace*)spaces[onSpaceIndex];
    propertySpace->newOwner(askingPlayer);
    emit boughtProperty(askingPlayer,givePlayer->getColour(), onSpaceIndex);
}


QList<Player *> Board::getPlayers()
{
    return players;
}

QList<Space *> Board::getSpaces()
{
    return spaces;
}

void Board::completeAuction(int player, int amount, int spaceIndex)
{
    PropertySpace* currentProperty = (PropertySpace*)spaces[spaceIndex];
    PropertyCard* card = bank->getCard(currentProperty->getName());
    bank->removeProperty(currentProperty->getName());
    players[player]->buyCard(card, amount);
    currentProperty->hasOwnership();
    currentProperty->newOwner(player);

    //emit signal to view something has been bought
    emit boughtProperty(player,players[player]->getColour(), spaceIndex);
}

void Board::checkBid(int player, int amount)
{
    bool bidOK = false;

    if (players[player]->checkTransaction(amount))
    {
        bidOK = true;
    }

    emit bidChecked(bidOK);
}

void Board::inJailPay()
{
    players[currentTurn]->changeMoney(-50);

    players[currentTurn]->getOutJail();

    emit inJailPaid();
}

/*  Author: Ho Yuet
 *  Sells a n amount of buildings from a player
 */
void Board::sellBuildings(QColor colour, int amount)
{
    Player* player = players[currentTurn];
    QList<PropertyCard*> playerProperties = player->getProperties();
    QList<PropertyCard*> affectedCards;
    int priceBuilding = 0;
    int originalAmount = amount;
    while(amount > 0)
    {
        foreach(PropertyCard* card, playerProperties)
        {
            if (card->getColour() == colour && card->canRemoveBuilding())
            {
                priceBuilding = card->getBuildingPrice();
                card->removeBuilding();
                affectedCards.append(card);
                amount--;
                if(amount <= 0)
                    break;
            }
        }
    }
    player->changeMoney(int((priceBuilding/2)) * originalAmount); // give money of the sold buildings at half price

    int position = 0;
    // notify view
    foreach(PropertyCard* affectedCard, affectedCards)
    {
        position = getIndexSpaceFromPropertyName(affectedCard->getName());
        emit buildingsAreBuilded(position,affectedCard->getTypeBuilding(),affectedCard->getAmountBuildings());
    }
}

/*Author: Ho Yuet
 * Checks which colour of properies has sellable buildings of the current player
 */
void Board::checkBuildingsSellable()
{
    QList<PropertyCard*> cards;
    foreach(PropertyCard* card, players[currentTurn]->getProperties())
    {
        if(card->getAmountBuildings() != 0) // if the card has buildings
        {
            if (!checkColourAlreadyInCards(cards, card->getColour()))
                cards.append(card);
        }
    }
    emit buildingsAreSellable(cards, SELL);
}

/*  Author: Ho Yuet
 * Notifies view for changes of owners after loading
 */
void Board::reloadSpaces()
{
    int iterator = 0;
    foreach(Space* space, spaces)
    {
        if (space->getType() == Space::Type::COMPANY ||space->getType() == Space::Type::STREET || space->getType() == Space::Type::STATION)
        {
            PropertySpace* propertySpace = (PropertySpace*) space;
            int owner = propertySpace->getOwner();
            if (propertySpace->checkIfOwned())
                emit boughtProperty(owner, players[owner]->getColour(),iterator);
        }
        iterator++;
    }
}


/*
 * gives the max amount of sellable buildings of a given colour
 */
void Board::getMaxAmountSellableBuilding(QColor colour)
{
    int amountBuildings = 0;
    QList<PropertyCard*>cards = players[currentTurn]->getProperties();
    foreach (PropertyCard* card, cards)
    {
        if (card->getColour() == colour)
            amountBuildings += card->getAmountBuildings();
    }

    emit giveAmountSellableBuildings(amountBuildings);
}


void Board::inJailRoll()
{
    rollDices();

    int firstDice = dices[0]->getRolledSymbol().toInt();
    int secondDice = dices[1]->getRolledSymbol().toInt();

    if (firstDice == secondDice)
    {
        players[currentTurn]->getOutJail();

        emit inJailRolled(true, firstDice, secondDice);

        finishTurn(firstDice + secondDice);
    }
    else
    {
        players[currentTurn]->rollInJail();
        emit inJailRolled(false, firstDice, secondDice);

        if (players[currentTurn]->hasRolledThreeTimes())
        {
            inJailPay();
        }
    }
}

void Board::inJailUseCard()
{
    players[currentTurn]->useJailCard();
    players[currentTurn]->getOutJail();
    emit inJailCardUsed();
}

void Board::retirePlayer()
{
    Space* currentSpace = spaces[players[currentTurn]->getCurrentPosition()];
    QList<PropertyCard*> properties = players[currentTurn]->getProperties();

    if (currentSpace->getType() != Space::Type::STREET && currentSpace->getType() != Space::Type::STATION && currentSpace->getType() != Space::Type::COMPANY)
    {
        foreach(PropertyCard* property, properties)
        {
            bank->addProperty(*property);
            players[currentTurn]->removePropertyCard(property);
            property->removeAllBuildings();

            emit buildingsAreBuilded(getIndexSpaceFromPropertyName(property->getName()), PropertyCard::TypeBuilding::HOTEL, property->getAmountBuildings());
        }
    }
    else
    {
        int owner = ((PropertySpace*)currentSpace)->getOwner();

        foreach(PropertyCard* property, properties)
        {
            players[owner]->addPropertyCard(property);

            //emit boughtProperty(owner, players[owner]->getColour(), );
        }
    }
}


PropertyCard * Board::getBankPropertyCard(QString name)
{
    return bank->getCard(name);
}

/*  Author: Ho Yuet
 *  Moves the current-in-turn player n amount of spaces
 * 1 argument: number of spaces to move
 */
void Board::movePlayer(int numberSpaces)
{
    players[currentTurn]->move((players[currentTurn]->getCurrentPosition() + numberSpaces) % SIZE_OF_BOARD);
}

/* Author: Ho Yuet
 * Reads the spaces from a file and inserts it to spaces
 */
void Board::insertSpaces()
{
    QFile spacesFile("../MonopolySpaces.txt");  // file is outside of the projectfile
    QStringList spaceInfo;

    if (!spacesFile.exists())
    {
        qDebug() << "MonopolySpaces file does not exist";
        return;
    }
    if (!spacesFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Can't open MonopolySpaces file";
        return;
    }

    QTextStream in(&spacesFile);
    while (!in.atEnd())
    {
        QString line = in.readLine();   // read line by line
        spaceInfo = line.split(",");    // split line by ,

        if (spaceInfo[0] == "Start")
            spaces.append(new StartSpace);
        else if(spaceInfo[0] == "Chest")
            spaces.append(new CommunityChestSpace);
        else if(spaceInfo[0] == "Street")
            spaces.append(new StreetSpace(spaceInfo[3].toInt(),spaceInfo[1],getColorFromString(spaceInfo[2])));
        else if(spaceInfo[0] == "Money")
            spaces.append(new MoneySpace(spaceInfo[1].toInt()));
        else if(spaceInfo[0] == "Chance")
            spaces.append(new ChanceSpace);
        else if (spaceInfo[0] == "Jail")
            spaces.append(new JailSpace);
        else if (spaceInfo[0] == "Auction")
            spaces.append(new AuctionSpace);
        else if (spaceInfo[0] == "Parking")
            spaces.append(new ParkingSpace);
        else if(spaceInfo[0] == "Bus")
            spaces.append(new BusSpace);
        else if (spaceInfo[0] == "To Jail")
            spaces.append(new GoToJailSpace);
        else if(spaceInfo[0] == "Station")
            spaces.append(new StationSpace(spaceInfo[3].toInt(),spaceInfo[1],getColorFromString(spaceInfo[2])));
        else if(spaceInfo[0] == "Company")
            spaces.append(new CompanySpace(spaceInfo[3].toInt(),spaceInfo[1], getColorFromString(spaceInfo[2])));

    }
    spacesFile.close();
}

void Board::insertCommunityCards()
{
    QFile cardsFile("../CommunityChestCards.txt");  // file is outside of the projectfile
    QStringList cardInfo;

    if(!cardsFile.exists())
    {
        qDebug() << "CommunityChestCards file does not exist";
        return;
    }

    if (!cardsFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Can't open CommunityChestCards file";
        return;
    }

    QTextStream in(&cardsFile);
    while(!in.atEnd())
    {
        QString line = in.readLine();
        cardInfo = line.split(",");

        if(line.contains("*"))
        {
            continue;
        }
        else if(cardInfo[0] == "Money")
        {
            communityChestCards.append(new MoneyCommunityCard(cardInfo[1], cardInfo[2].toInt()));
        }
        else if (cardInfo[0] == "MoneyAll")
        {
            communityChestCards.append(new MoneyAllCommunityCard(cardInfo[1], cardInfo[2].toInt()));
        }
        else if (cardInfo[0] == "MoneyProp")
        {
            communityChestCards.append(new MoneyPropCommunityCard(cardInfo[1]));
        }
        else if (cardInfo[0] == "ToGo")
        {
            communityChestCards.append(new ToGoCommunityCard(cardInfo[1]));
        }
        else if (cardInfo[0] == "ToJail")
        {
            communityChestCards.append(new ToJailCommunityCard(cardInfo[1]));
        }
        else if (cardInfo[0] == "OutOfJail")
        {
            communityChestCards.append(new OutOfJailCommunityCard(cardInfo[1]));
        }
    }

    cardsFile.close();
}

/*Author: Ho Yuet
 * Converts a string color to a QColor
 * 1 argument: color in QString
 */
QColor Board::getColorFromString(QString color)
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

/*  Author: Sebastiaan
 * Rolls the dices and notifies View the results
 */
void Board::rollDices()
{
    for (int i = 0; i < NUMBER_OF_DICES; i++)
    {
        dices[i]->rollDice();
    }

    if (!(players[currentTurn]->isInJail()))
        emit rolled(dices[0]->getRolledSymbol(), dices[1]->getRolledSymbol(), dices[2]->getRolledSymbol());  // notify view

}

/*  Author: Ho Yuet
 * Checks if the given player has the full monopoly of a given colour
 * 2 arguments: Player to check, colour
 */
bool Board::checkHasFullMonopoly(const Player &player, QColor colour)const
{
    if (bank->foundColourInBank(colour)) // if there is a same colour in the bank
        return false;
    // check in other players
    foreach(Player* p, players)
    {
        if (p->getNumberPlayer() != player.getNumberPlayer())   // don't check the player self
        {
            if(p->checkColourInProperty(colour))
                return false;
        }
    }
    // if there are no same colour found
    return true;
}

bool Board::checkHasMajority(const Player &player, QColor colour) const
{
    int numberOfColourCards = getNumberOfColourCards(colour);
    int numberOfPlayerCards = getNumberOfPlayerCards(player, colour);

    if (numberOfPlayerCards == (numberOfColourCards - 1))
    {
        return true;
    }

    return false;
}

void Board::goToJail()
{
    int currentPosition = players[currentTurn]->getCurrentPosition();
    int jailPosition = findSpace(Space::Type::JAIL);

    players[currentTurn]->putInJail();

    int steps = (jailPosition - currentPosition) % SIZE_OF_BOARD;
    movePlayer(steps);

    emit movedToJail();
}

void Board::goToStart()
{
    int currentPosition = players[currentTurn]->getCurrentPosition();
    int startPosition = findSpace(Space::Type::START);

    int steps = (startPosition - currentPosition) % SIZE_OF_BOARD;
    finishTurn(steps);
}

QList<PropertyCard *> Board::getBankPropertyCards() const
{
    return bank->getCards();
}

int Board::getNumberOfColourCards(QColor colour)const
{
    int numberOfColourCards = 0;

    numberOfColourCards = bank->getNumberOfColourCards(colour);

    foreach (Player* player, players)
    {
        foreach (PropertyCard* card, player->getProperties())
        {
            if (card->getColour() == colour)
                numberOfColourCards++;
        }
    }

    return numberOfColourCards;
}

int Board::getNumberOfPlayerCards(const Player &player, QColor colour) const
{
    int numberOfPlayerCards = 0;

    foreach (PropertyCard* card, player.getProperties())
    {
        if (card->getColour() == colour)
            numberOfPlayerCards++;
    }

    return numberOfPlayerCards;
}

int Board::getPips()const
{
    int totalPips = 0;
    int pips;

    foreach (Dice* dice, dices)
    {
        pips = dice->getRolledSymbol().toInt();

        if (pips != 0)
        {
            totalPips += pips;
        }
    }

    return totalPips;
}


void Board::addBusTicket()
{
    if (!(bustickets.isEmpty()))
    {
        players[currentTurn]->takeBusTicket(bustickets.takeLast());
        emit busTicketDone(1);
    }
    else
    {
        emit busTicketDone(0);
    }
}

/* Author: Sebastiaan
 * Moves current player to the nearest Chance space
 */
void Board::moveToChance()
{
    int i = players[currentTurn]->getCurrentPosition() + 1;

    while (spaces[i]->getType() != Space::Type::CHANCE && spaces[i]->getType() != Space::Type::CHEST)
    {
        i = (i + 1) % SIZE_OF_BOARD;
    }
    finishTurn(i - players[currentTurn]->getCurrentPosition());

}

/* Author: Sebastiaan
 * Moves current player to the nearest unowned property
 */
void Board::moveToUnownedProperty()
{
    int i = players[currentTurn]->getCurrentPosition() + 1;

    //Check if unowned space available till currentPosition
    while(i != players[currentTurn]->getCurrentPosition() && ((spaces[i]->getType() != Space::Type::STREET && spaces[i]->getType() != Space::Type::COMPANY && spaces[i]->getType() != Space::Type::STATION) || ((PropertySpace*)spaces[i])->checkIfOwned()))
    {
        i = (i + 1) % SIZE_OF_BOARD;
    }

    if (i == players[currentTurn]->getCurrentPosition())
    {
        //Check if space is unmortgaged till currentPosition
        while(i != players[currentTurn]->getCurrentPosition() && ((spaces[i]->getType() != Space::Type::STREET && spaces[i]->getType() != Space::Type::COMPANY && spaces[i]->getType() != Space::Type::STATION) || ((PropertySpace*)spaces[i])->getOwner() == players[currentTurn]->getNumberPlayer()))
        {
            i = (i + 1) % SIZE_OF_BOARD;
        }
    }

    if(i != players[currentTurn]->getCurrentPosition())
    {
        int steps = i - players[currentTurn]->getCurrentPosition();
        finishTurn(steps);
    }
}

/* Author: Ho Yuet
 * Current player buys the property he's standing on
 */
void Board::buyProperty()
{
    int currentSpace = players[currentTurn]->getCurrentPosition();
    PropertySpace* currentProperty = (PropertySpace*)spaces[currentSpace];
    PropertyCard* card = bank->getCard(currentProperty->getName());

    bank->removeProperty(currentProperty->getName());
    players[currentTurn]->buyCard(card);
    currentProperty->newOwner(currentTurn);
    currentProperty->hasOwnership();
    currentProperty->newOwner(currentTurn);

    //emit signal to view something has been bought
    emit boughtProperty(currentTurn,players[currentTurn]->getColour(), currentSpace);

}

void Board::calculateBusSelection()
{
    int i = SIZE_OF_SIDE;

    while (players[currentTurn]->getCurrentPosition() >= i)
    {
        i+= SIZE_OF_SIDE;
    }

    i = i % SIZE_OF_BOARD;

    emit busSelectionCalculated(players[currentTurn]->getCurrentPosition(), i);
}

void Board::takeBus(int newPos)
{
    int numberSpaces = newPos - players[currentTurn]->getCurrentPosition();

    finishTurn(numberSpaces);
}

void Board::doDiceMove()
{    
    if (players[currentTurn]->isInJail())
    {
        emit isInJail(players[currentTurn]->hasJailCard());
    }
    else
    {
        rollDices();
        diceMoveOutOfJail();
    }

    players[currentTurn]->addRoll(dices);

}

/*  Author: Sebastiaan
 * Switches the turn to the next player
 */
void Board::switchTurn()
{
    currentTurn = (currentTurn + 1) % players.count();
    emit turnSwitched(currentTurn);

    if (players[currentTurn]->hasBusTickets() && !players[currentTurn]->isInJail())
    {
        emit hasBusTickets();
    }

}

/*  Author: Ho Yuet
*  Mortgages or Unmortgages the given property
*/
void Board::mortgageProperty(const QString name)
{
    Player* currentPlayer = players[currentTurn];
    PropertyCard* card = currentPlayer->getPropertyCard(name);

    if (card == NULL) // if there is no card found or it's already mortgaged
        return;

    int mortgageValue = card->getPriceMortgage();
    if (!card->checkIfMortgaged())   // if the player wants to mortgage property
    {
        if (card->getAmountBuildings() > 0)
        {
            emit unableToMortgage();
            return;
        }

	// need to sell all houses/hotels/skyscrapers
        card->switchMortgaged();
        currentPlayer->changeMoney(mortgageValue);   // add money from mortgage
    }
    else if (card->checkIfMortgaged())   // lift mortgage
    {
        currentPlayer->changeMoney(-(int)(mortgageValue * 1.1)); // mortgage value + 10%
        card->switchMortgaged();
    }
}

/*  Author: Ho Yuet
 *  checks if the current player has any properties that can build buildings
 */
void Board::checkBuildingBuyable()
{
    QList<PropertyCard*> cards;
    foreach(PropertyCard* card, players[currentTurn]->getProperties())
    {
        bool hasMonopoly = checkHasFullMonopoly(*players[currentTurn], card->getColour());
        // if the card is a station or the player has majority or full monopoly
        if((card->canBuildBuildings(hasMonopoly) && (checkHasMajority(*players[currentTurn], card->getColour())) || card->getType() == PropertyCard::PropertyType::STATION))
        {
            if (!checkColourAlreadyInCards(cards, card->getColour()))
                cards.append(card);
        }
    }
    emit buildingsAreBuyable(cards, BUY);
}

/*  Author: Ho Yuet
 * Calculates how many buildings a colour can have from the current player
 */
void Board::getMaxAmountBuildableBuilding(QColor colour)
{
    int amountBuildings = 0;
    QList<PropertyCard*>cards = players[currentTurn]->getProperties();
    foreach (PropertyCard* card, cards)
    {
        bool hasMonopoly = checkHasFullMonopoly(*players[currentTurn], card->getColour());

        if (card->getColour() == colour && card->canBuildBuildings(hasMonopoly))
            amountBuildings += card->getAmountBuildableBuildings();
    }

    emit giveAmountBuildableBuildings(amountBuildings);
    return;
}

/*  Author: Ho Yuet
 * Builds buildings on a given colour with the given amount for the given player
 */
void Board::buildBuildings(QColor colour, int amount)
{
    Player* currentPlayer = players[currentTurn];
    int priceBuilding = 0;
if (currentPlayer->checkIfColourMortgaged(colour))
    {
        emit unableToBuildBuildings();
        return;
    }

    // find the price of the building
    foreach(PropertyCard* card, currentPlayer->getProperties())
    {
        if (colour == card->getColour())
        {
            priceBuilding = card->getBuildingPrice();
            break;
        }
    }
    currentPlayer->changeMoney(-(amount*priceBuilding)); // use money to buy buildings

    QList<PropertyCard*> changedCards;
    QList<PropertyCard*> playerProperties = currentPlayer->getProperties();
    //keep building buildings until amount of buildings == 0

    while(amount > 0)
    {
        foreach(PropertyCard* card, playerProperties)
        {
            bool hasMonopoly = checkHasFullMonopoly(*players[currentTurn], card->getColour());
            if (card->getColour() == colour && card->canBuildBuildings(hasMonopoly))
            {
                changedCards.append(card);
                card->buildBuilding();
                amount--;
                if (amount <= 0)
                    break;
            }
        }
    }
    // notify view for changes
    foreach (PropertyCard* card, changedCards)
        {
            int position = getIndexSpaceFromPropertyName(card->getName());
            int buildings = card->getAmountBuildings();

            emit buildingsAreBuilded(position, card->getTypeBuilding(), buildings);
        }
}

/*  Author: Ho Yuet
 *  checks in a given list if a card is already in the list
 * returns true if the colour in already in the list, false otherwise
 */
bool Board::checkColourAlreadyInCards(const QList<PropertyCard *> cards, QColor colour)const
{
    foreach(PropertyCard* card, cards)
    {
        if(card->getColour() == colour)
            return true;
    }
    return false;
}

/*  Author: Ho Yuet
 *  returns the positon of the PropertySpace with the given name
 */
int Board::getIndexSpaceFromPropertyName(QString propertyName)
{
    int indexSpace = 0;
    foreach(Space* space, spaces)
    {
        if (space->getType() == Space::Type::STATION || space->getType() == Space::Type::STREET)
        {
            PropertySpace* thisSpace = (PropertySpace*) space;
            if (thisSpace->getName() == propertyName)
                return indexSpace;
        }
        indexSpace++;
    }
    return 0;
}

CommunityChestCard *Board::getRandomCommChestCard()
{
    CommunityChestCard* card = communityChestCards.takeFirst();

    communityChestCards.append(card);

    return card;
}

QList<CommunityChestCard *> Board::getCommunityChestCards()
{
    return communityChestCards;
}

void Board::doTransaction(int amount)
{
    players[currentTurn]->changeMoney(amount);
}

int Board::getCurrentTurn() const
{
    return currentTurn;
}

void Board::checkStart(int oldPos, int newPos)
{
    if (newPos < oldPos && !(players[currentTurn]->isInJail()))
    {
        players[currentTurn]->changeMoney(200);
        emit passedStart();
    }
}

bool Board::checkDoublesThrice()
{
   if(players[currentTurn]->checkDoublesTwice() && dices[0]->getRolledSymbol().toInt() == dices[1]->getRolledSymbol().toInt() && dices[0]->getRolledSymbol().toInt() != dices[2]->getRolledSymbol().toInt())
   {
       return true;
   }
   else
   {
       return false;
   }
}

void Board::diceMoveOutOfJail()
{
    if (checkDoublesThrice())
    {
        goToJail();
    }
    else
    {
        if ((dices[2]->getRolledSymbol()).toInt() != 0)
        {
            if (dices[0]->getRolledSymbol().toInt() == dices[1]->getRolledSymbol().toInt() && dices[0]->getRolledSymbol().toInt() == dices[2]->getRolledSymbol().toInt())
                emit rolledTriple();
            else
                finishTurn((dices[0]->getRolledSymbol()).toInt() + (dices[1]->getRolledSymbol()).toInt() + (dices[2]->getRolledSymbol()).toInt());
        }
        else if(dices[2]->getRolledSymbol().compare("MONOPOLY") == 0)
        {
            finishTurn((dices[0]->getRolledSymbol()).toInt() + (dices[1]->getRolledSymbol()).toInt());
            moveToUnownedProperty();
        }
        else if (dices[2]->getRolledSymbol().compare("BUS") == 0)
        {
            finishTurn((dices[0]->getRolledSymbol()).toInt() + (dices[1]->getRolledSymbol()).toInt());
            emit busRolled();
        }

        if (dices[0]->getRolledSymbol().toInt() == dices[1]->getRolledSymbol().toInt() && dices[0]->getRolledSymbol().toInt() != dices[2]->getRolledSymbol().toInt() && !players[currentTurn]->isInJail())
        {
            emit rolledDouble();
        }
    }
}

void Board::finishTurn(int numberSpaces)
{

    int oldPos = players[currentTurn]->getCurrentPosition();

    movePlayer(numberSpaces);

    spaces[players[currentTurn]->getCurrentPosition()]->doSpaceMove(*this);

    checkStart(oldPos, players[currentTurn]->getCurrentPosition());

}

int Board::findSpace(Space::Type type) const
{
    int iterator = 0;

    foreach (Space* space, spaces)
    {

        if (space->getType() == type)
        {
            return iterator;
        }

        iterator++;
    }

    return -1;
}

/* Author: Ho Yuet
 * load
 */
void Board::read(const QJsonObject &json)
{
    // spaces
    for(int i = 0; i < spaces.size();i++)
    {
        delete spaces[i];
    }
    if (!spaces.isEmpty())  // remove garbage
        spaces.clear();
    QJsonArray spacesArray = json["spaces"].toArray();

    for (int i = 0; i < spacesArray.size();i++)
    {
        QJsonObject spacesObject = spacesArray[i].toObject();
        instantiateWhichSpace(spacesObject);
    }
    // players
    for(int i = 0; i < players.size();i++)
    {
        delete players[i];
    }
    if(!players.isEmpty())// remove garbage
        players.clear();
    QJsonArray playersArray = json["players"].toArray();
    for (int i = 0; i < playersArray.size();i++)
    {
        QJsonObject playerObject = playersArray[i].toObject();
        if (playerObject.isEmpty())
            players.append(NULL);
        else
        {
            Player* player = new Player;
            player->read(playerObject);
            players.append(player);
        }
    }
    //bank
    QJsonObject bankObject = json["bank"].toObject();
    bank->read(bankObject);


    //dice
    for(int i = 0; i < dices.size();i++)
    {
        delete dices[i];
    }
    if (!dices.isEmpty())// remove garbage
        dices.clear();
    QJsonArray dicesArray = json["dices"].toArray();
    for (int i = 0; i < dicesArray.size();i++)
    {
        QJsonObject diceObject = dicesArray[i].toObject();
        Dice* dice = new Dice;
        dice->read(diceObject);
        dices.append(dice);
    }
    //bus

    currentTurn = json["currentTurn"].toInt();
    emit reload(players.count());
    reloadSpaces();
    emit turnSwitched(currentTurn);
    reloadBuildings();

}

/*Author: Ho Yuet
 * Save
 */
void Board::write(QJsonObject &json) const
{
    //spaces
    QJsonArray spaceArray;
    foreach(const Space* space, spaces)
    {
        QJsonObject spaceObject;
        space->write(spaceObject);
        spaceArray.append(spaceObject);
    }
    json["spaces"] = spaceArray;

    // players

    QJsonArray playerArray;
    foreach(const Player* player, players)
    {
        if (player == NULL)
            playerArray.append(NULL);
        else
        {
            QJsonObject playerObject;
            player->write(playerObject);
            playerArray.append(playerObject);
        }


    }
    json["players"] = playerArray;

    // bank
    QJsonObject bankObject;
    bank->write(bankObject);
    json["bank"] = bankObject;

    //dice
    QJsonArray diceArray;
    foreach(const Dice* dice, dices)
    {
        QJsonObject diceObject;
        dice->write(diceObject);
        diceArray.append(diceObject);
    }
    json["dices"] = diceArray;
    //bus
    json["currentTurn"] = currentTurn;

}

/*  Author: Ho Yuet
 *  Instatiates and adds the correct type of space in spaces
 */
void Board::instantiateWhichSpace(const QJsonObject &json)
{
    switch (Space::Type(qRound(json["type"].toDouble()))) {
    case Space::Type::START:
    {
        StartSpace* space = new StartSpace;
        space->read(json);
        spaces.append(space);
        break;
    }
    case Space::Type::CHEST:
    {
        CommunityChestSpace* space = new CommunityChestSpace;
        space->read(json);
        spaces.append(space);
        break;
    }
    case Space::Type::CHANCE:
    {
        ChanceSpace* space = new ChanceSpace;
        space->read(json);
        spaces.append(space);
        break;
    }
    case Space::Type::STREET:
    {
        StreetSpace* space = new StreetSpace;
        space->read(json);
        spaces.append(space);
        break;
    }
    case Space::Type::MONEY:
    {
        MoneySpace* space = new MoneySpace;
        space->read(json);
        spaces.append(space);
        break;
    }
    case Space::Type::JAIL:
    {
        JailSpace* space = new JailSpace;
        space->read(json);
        spaces.append(space);
        break;
    }
    case Space::Type::BUS:
    {
        BusSpace* space = new BusSpace;
        space->read(json);
        spaces.append(space);
        break;
    }
    case Space::Type::COMPANY:
    {
        CompanySpace* space = new CompanySpace;
        space->read(json);
        spaces.append(space);
        break;
    }
    case Space::Type::STATION:
    {
        StationSpace* space = new StationSpace;
        space->read(json);
        spaces.append(space);
        break;
    }
    case Space::Type::SPECIAL:
    {
        ParkingSpace* space = new ParkingSpace;
        space->read(json);
        spaces.append(space);
        break;
    }
    case Space::Type::AUCTION:
    {
        AuctionSpace* space = new AuctionSpace;
        space->read(json);
        spaces.append(space);
        break;
    }
    case Space::Type::TOJAIL:
    {
        GoToJailSpace* space = new GoToJailSpace;
        space->read(json);
        spaces.append(space);
        break;
    }
    default:
        break;
    }
}

/*
 * Author: Ho Yuet
 * Refreshes all buildings after loading
 */
void Board::reloadBuildings()
{
    foreach(Player* player, players)
    {
        QList<PropertyCard*> cards = player->getProperties();
        foreach(PropertyCard* card, cards)
        {
            if (card->getAmountBuildings() > 0) // if the card has buildings
            {
                int indexPosition = getIndexSpaceFromPropertyName(card->getName());

                emit buildingsAreBuilded(indexPosition, card->getTypeBuilding(), card->getAmountBuildings());
            }
        }
    }
}


