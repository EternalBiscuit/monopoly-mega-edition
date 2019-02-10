// Author: Ho Yuet, Sebastiaan
#ifndef BOARDVIEW_H
#define BOARDVIEW_H

#include <QObject>
#include <QGraphicsScene>
#include "dicedialog.h"
#include "board.h"
#include "propertycard.h"

class SpaceView;
class PlayerView;
class AmountPlayerDialog;
class Game;
class PlayerInfoView;
class BuyDialog;
class PropertiesDialog;
class BuildableBuildingsDialog;
class RentDialog;
class AuctionDialog;
class JailDialog;
class MonopolyBoardView;
class NegotiationDialog;

class BoardView: public QGraphicsScene
{
    Q_OBJECT
public:
    BoardView();
private:
    static const int SIZE_OF_BOARD = 52;
    MonopolyBoardView* monopolyBoard;
    QList<SpaceView*> spaces;   // list of all spaces
    QList<PlayerInfoView*>playerInfo;   // list of all player informations
    QList<PlayerView*> players; // list of all players icon
    QPushButton* rollButton;    // on click rolls the dice
    QPushButton* endTurnButton; // on click ends the turn of the current player
    QPushButton* busTicketButton; //on click uses busticket
    QPushButton* buyBuildingsButton; // on click prompt buy buildings
    QPushButton* sellBuildingsButton;   // on click prompt sell buildings
    QPushButton* saveGameButton;    // on click save game
    QPushButton* loadGameButton;
    DiceDialog* diceDialog;     // dialog for dice
    AmountPlayerDialog* amountPlayerDialog; // dialog for choosing the amount of players
    BuyDialog* buyDialog;       // dialog for buying a property
    PropertiesDialog* propertyDialog;       // dialog for showing the properties
    RentDialog* rentDialog; //dialog for showing paid rent
    BuildableBuildingsDialog* buildDialog;
    AuctionDialog* auctionDialog;
    NegotiationDialog* negotiationDialog;
    JailDialog* jailDialog;
    Game* game;     // the game itself
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void changeSelectable(bool mode);   // disables all selectable spaces
    void connectOwnerView();
    void connectMoneySpaces();
    void connectBuildings();
    void connectPropertySpaces();
    void connectJailDialog();
    void connectCommunityChest();
    void connectPlayers();
    void reloadSpaces();
public slots:
	void showBuilingErrorMessage();
    void showMortgageErrorMessage();

    void getNumberPlayers(int numberPlayers);   // gets the number of players for constructor
    void movePlayer(int currentPlayer, int position);   // moves a player to a position
    void selectBusTicketSpaces(int currentPosition, int endPosition);
    void showPlayerProperties(int numberPlayer);    // shows the properties a player has
    void turnSwitched(int currentPlayer);  // shows who the current player is
    void propertyHasBeenBought(int player, QColor colour, int space);
    void buildBuildings(int indexPosition, PropertyCard::TypeBuilding building, int amount);
    void showStartMessage();
    void showMoneyMessage(int amount);
    void showToJailMessage();
private slots:
    void showBusTicketButton(); // shows the bus button
    void useBusTicket();    // uses the bus
    void moveToAnySpace();
    void rollAgain();
    void showCommunityChestMessage(QString description, int value);
    void showNotEnoughMoneyMessage();
    void showBrokeMessage(int numberPlayer);
void justLoaded(int amountPlayers);
    void removeAllSpaceOwners();
    void savedSuccessfully();

signals:
    void spaceSelected(int newPos); // let's you select a space
    void playerRetired();

};

#endif // BOARDVIEW_H
