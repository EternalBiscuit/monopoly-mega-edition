#include "boardview.h"
#include "monopolyboardview.h"
#include "spaceview.h"
#include "playerinfoview.h"
#include "playerview.h"
#include "amountplayerdialog.h"
#include "game.h"
#include "buydialog.h"
#include "propertiesdialog.h"
#include "transactiondialog.h"
#include "ownerview.h"
#include "buildablebuildingsdialog.h"
#include "buildbuildingdialog.h"
#include "rentdialog.h"
#include "buildingview.h"
#include "auctiondialog.h"
#include "space.h"
#include "moneyspace.h"
#include "streetspace.h"
#include "companyspace.h"
#include "stationspace.h"
#include "jaildialog.h"
#include "communitychestcard.h"
#include "negotiationdialog.h"

#include <QPixmap>
#include <QDebug>
#include <QCursor>
#include <QMessageBox>
#include <QGraphicsItem>


/*  Authors: Ho Yuet, Sebastiaan
 * Constructor of BoardView
 */
BoardView::BoardView()
{
    monopolyBoard = new MonopolyBoardView;  // board image
    addItem(monopolyBoard);

    // South
    spaces.append(new SpaceView(862,633,97,75,0,0));  // start space
    for(int i = 1; i < 3; i++)
    {
        spaces.append(new SpaceView(862-(72*i),633,72,75,0,i));
    }
    spaces.append(new SpaceView(643,633,76,75,0,3));
    spaces.append(new SpaceView(585,633,59,75,0,4));
    spaces.append(new SpaceView(527,633,59,75,0,5));  // income tax
    spaces.append(new SpaceView(461,633,65,75,0,6));  // kings cross station
    for (int i = 1; i < 3; i++)
    {
        spaces.append(new SpaceView(460-(53*i),633,53,75,0,6+i));
    }
    spaces.append(new SpaceView(298,633,56,75,0,9));  // chance space
    spaces.append(new SpaceView(236,633,60,75,0,10));  // gas company
    spaces.append(new SpaceView(166,633,70,75,0,11));
    spaces.append(new SpaceView(109,633,56,75,0,12));
    spaces.append(new SpaceView(0,633,108,75,0,13)); // jail space

    // West
    // spaces[14] auction space
    for (int i = 0; i < 3; i++)
    {
        spaces.append(new SpaceView(33,555-(45*i),45,109,90,14+i));
    }
    spaces.append(new SpaceView(33,420,46,109,90,17)); // electric company
    spaces.append(new SpaceView(32,373,48,109,90,18));
    for (int i = 0; i < 2; i++) // spaces[21] marylebone station
    {
        spaces.append(new SpaceView(33,325-(48*i),48,109,90,19+i));
    }

    spaces.append(new SpaceView(33,230,47,109,90,21));
    spaces.append(new SpaceView(33,184,46,109,90,22)); // community chest

    for (int i = 0; i < 3; i++)
    {
        spaces.append(new SpaceView(33,138-(46*i),46,109,90,23+i));
    }
    spaces.append(new SpaceView(0,0,110,76,0,26)); // free parking

    // North ->
    spaces.append(new SpaceView(110,0,56,76,180,27));
    spaces.append(new SpaceView(167,0,69,76,180,28));  // chance space
    spaces.append(new SpaceView(236,0,61,76,180,29));
    spaces.append(new SpaceView(297,0,57,76,180,30));
    spaces.append(new SpaceView(354,0,55,76,180,31));
    spaces.append(new SpaceView(409,0,53,76,180,32));  // bus space
    spaces.append(new SpaceView(462,0,67,76,180,33));  // fenchurch street station
    spaces.append(new SpaceView(529,0,56,76,180,34));
    spaces.append(new SpaceView(586,0,57,76,180,35));
    spaces.append(new SpaceView(643,0,77,76,180,36)); // water works
    spaces.append(new SpaceView(720,0,68,76,180,37));
    spaces.append(new SpaceView(789,0,74,76,180,38));
    spaces.append(new SpaceView(863,0,94,76,0,39));  // go to jail space

    // East
    spaces.append(new SpaceView(886,53,47,96,270,40));
    spaces.append(new SpaceView(887,100,45,96,270,41));
    spaces.append(new SpaceView(887,145,45,96,270,42));
    spaces.append(new SpaceView(887,190,45,96,270,43));    // community chest
    spaces.append(new SpaceView(887,235,47,96,270,44));
    spaces.append(new SpaceView(887,282,48,96,270,45));    // liverpool station
    spaces.append(new SpaceView(887,330,47,96,270,46));    // chance
    spaces.append(new SpaceView(887,378,47,96,270,47));    // birthday gift
    spaces.append(new SpaceView(887,425,47,96,270,48));
    spaces.append(new SpaceView(887,472,47,96,270,49));
    spaces.append(new SpaceView(887,519,45,96,270,50));    // bank deposit
    spaces.append(new SpaceView(887,564,45,96,270,51));
    for (int i = 0; i < SIZE_OF_BOARD; i++)
        addItem(spaces[i]);

    diceDialog = new DiceDialog();
    rollButton = new QPushButton(tr("Roll"));
    rollButton->move(1000, 680);
    addWidget(rollButton);

    amountPlayerDialog = new AmountPlayerDialog();
    connect(amountPlayerDialog, SIGNAL(selected(int)), this, SLOT(getNumberPlayers(int)));
    amountPlayerDialog->exec();

    endTurnButton = new QPushButton(tr("End Turn"));
    addWidget(endTurnButton);
    endTurnButton->move(1120,0);
    endTurnButton->setEnabled(false);

    busTicketButton = new QPushButton(tr("Bus Ticket"));
    busTicketButton->setEnabled(false);
    busTicketButton->move(1120, 680);
    addWidget(busTicketButton);

    buyDialog = new BuyDialog;

    propertyDialog = new PropertiesDialog;

    rentDialog = new RentDialog();

    buildDialog = new BuildableBuildingsDialog;

    jailDialog = new JailDialog;

    buyBuildingsButton = new QPushButton("Buy Buildings");
    buyBuildingsButton->move(1120,630);
    addWidget(buyBuildingsButton);

sellBuildingsButton = new QPushButton("Sell Buildings");
    sellBuildingsButton->move(1120,580);
    addWidget(sellBuildingsButton);

    saveGameButton = new QPushButton("Save");
    saveGameButton->move(1000,630);
    addWidget(saveGameButton);

    loadGameButton = new QPushButton("Load");
    loadGameButton->move(1000,580);
    addWidget(loadGameButton);


    auctionDialog = new AuctionDialog(players.count());
    negotiationDialog = new NegotiationDialog;

    connect(game->getBoard(), &Board::negotiate, negotiationDialog, &NegotiationDialog::showNegotiation);
    connect(negotiationDialog, &NegotiationDialog::trade, game->getBoard(), &Board::trade);

    connect(propertyDialog->getTransactionDialog(), &TransactionDialog::trade, game->getBoard(), &Board::givePossibleTradeProperty);
    connect(propertyDialog->getTransactionDialog(), &TransactionDialog::mortgage, game->getBoard(), &Board::mortgageProperty);
    connect(game->getBoard(), &Board::turnSwitched, this, &BoardView::turnSwitched);

    connect(endTurnButton, SIGNAL(clicked(bool)), game->getBoard(), SLOT(switchTurn()));
    connect(rollButton, SIGNAL(clicked(bool)),  game->getBoard(), SLOT(doDiceMove()));
    connect(game->getBoard(), SIGNAL(rolled(const QString,const QString,const QString)), diceDialog, SLOT(showDialog(const QString,const QString,const QString)));
    connect(diceDialog, SIGNAL(busTicketChosen()), game->getBoard(), SLOT(addBusTicket()));
    connect(game->getBoard(), SIGNAL(busTicketDone(int)), diceDialog, SLOT(showBusTicket(int)));
    connect(diceDialog, SIGNAL(chanceChosen()), game->getBoard(), SLOT(moveToChance()));
    connect(game->getBoard(), SIGNAL(hasBusTickets()), this, SLOT(showBusTicketButton()));
    connect(busTicketButton, SIGNAL(clicked(bool)), this, SLOT(useBusTicket()));
    connect(buyDialog, SIGNAL(buyButtonClicked()), game->getBoard(), SLOT(buyProperty()));
    connect(busTicketButton, SIGNAL(clicked(bool)), game->getBoard(), SLOT(calculateBusSelection()));
    connect(game->getBoard(), SIGNAL(busSelectionCalculated(int,int)), this, SLOT(selectBusTicketSpaces(int,int)));
    connect(this, SIGNAL(spaceSelected(int)), game->getBoard(), SLOT(takeBus(int)));
    connect(game->getBoard(), SIGNAL(busRolled()), diceDialog, SLOT(showBusDialog()));
    connectOwnerView();
    connectMoneySpaces();
    connectBuildings();
    connectPropertySpaces();
    connectJailDialog();
    connectCommunityChest();
    connectPlayers();
    connect(buyDialog, SIGNAL(auctionButtonClicked(int)), auctionDialog, SLOT(showDialog(int)));
    connect(auctionDialog, SIGNAL(requestBid(int,int)), game->getBoard(), SLOT(checkBid(int,int)));
    connect(game->getBoard(), SIGNAL(bidChecked(bool)), auctionDialog, SLOT(processBid(bool)));
    connect(auctionDialog, SIGNAL(closeBuyDialog()), buyDialog, SLOT(close()));
    connect(auctionDialog, SIGNAL(auctionDone(int,int,int)), game->getBoard(), SLOT(completeAuction(int,int,int)));
    connect(game->getBoard(), SIGNAL(passedStart()), this, SLOT(showStartMessage()));
    connect(game->getBoard(), SIGNAL(movedToJail()), this, SLOT(showToJailMessage()));
    connect(game->getBoard(), SIGNAL(rolledTriple()), this, SLOT(moveToAnySpace()));
    connect(game->getBoard(), SIGNAL(rolledDouble()), this, SLOT(rollAgain()));
    connect(this, SIGNAL(playerRetired()), game->getBoard(), SLOT(retirePlayer()));
    connect(game->getBoard(), &Board::unableToBuildBuildings, this, &BoardView::showBuilingErrorMessage);

    connect(saveGameButton, &QPushButton::clicked, game, &Game::saveGame);
    connect(game, &Game::saved, this, &BoardView::savedSuccessfully);
    connect(loadGameButton, &QPushButton::clicked, game, &Game::loadGame);

    connect(game->getBoard(), &Board::unableToMortgage, this, &BoardView::showMortgageErrorMessage);

    connect(game->getBoard(), &Board::reload, this, &BoardView::justLoaded);

}

void BoardView::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (!(selectedItems().isEmpty()))
    {
        SpaceView* space = dynamic_cast<SpaceView*>(selectedItems()[0]);
        emit spaceSelected(space->getSpaceIndex());
        changeSelectable(false);
    }

    QGraphicsScene::mouseReleaseEvent(event);

}

void BoardView::showStartMessage()
{
    QMessageBox *startMessage = new QMessageBox();
    startMessage->setDefaultButton(QMessageBox::Ok);
    startMessage->setText("You passed start!\nYou get 200 pounds.");
    startMessage->setWindowTitle("Start");
    startMessage->exec();
}


/* Author: Sebastiaan, Ho Yuet
 * Gets the number of players
 */
void BoardView::changeSelectable(bool mode)
{
    foreach (SpaceView* space, spaces)
    {
        space->setFlag(QGraphicsItem::ItemIsSelectable, mode);
    }
}

/*  Author: Ho Yuet
 * connects the signals and slots for buying properties in view
 */
void BoardView::connectOwnerView()
{
    foreach(SpaceView* space, spaces)
    {
        connect(game->getBoard(),&Board::boughtProperty, this, &BoardView::propertyHasBeenBought);
    }
}

void BoardView::connectMoneySpaces()
{
    QList<Space*> spaces = game->getBoard()->getSpaces();

    foreach(Space* space, spaces)
    {
        if (space->getType() == Space::Type::MONEY)
        {
            MoneySpace* moneySpace = (MoneySpace*)space;
            connect(moneySpace, SIGNAL(moneyChanged(int)), this, SLOT(showMoneyMessage(int)));
        }
    }
}


/*  Author: Ho Yuet
 *  connects the signals and slots for building buildings
 */
void BoardView::connectBuildings()
{
    // build buildings
    connect(buyBuildingsButton, &QPushButton::clicked, game->getBoard(), &Board::checkBuildingBuyable);
    connect(game->getBoard(), &Board::buildingsAreBuyable, buildDialog, &BuildableBuildingsDialog::getProperties);
    connect(buildDialog, &BuildableBuildingsDialog::getMaxAmountBuyableBuildings, game->getBoard(), &Board::getMaxAmountBuildableBuilding);
    connect(game->getBoard(), &Board::giveAmountBuildableBuildings,buildDialog->getBuildBuildingDialog(), &BuildBuildingDialog::showBuildableBuildings);
    connect(buildDialog->getBuildBuildingDialog(), &BuildBuildingDialog::buildBuildings, game->getBoard(), &Board::buildBuildings);

//sell buildings
    connect(sellBuildingsButton, &QPushButton::clicked, game->getBoard(), &Board::checkBuildingsSellable);
    connect(game->getBoard(), &Board::buildingsAreSellable, buildDialog, &BuildableBuildingsDialog::getProperties);
    connect(buildDialog, &BuildableBuildingsDialog::getMaxAmountSellableBuildings, game->getBoard(), &Board::getMaxAmountSellableBuilding);
    connect(game->getBoard(), &Board::giveAmountSellableBuildings, buildDialog->getBuildBuildingDialog(), &BuildBuildingDialog::showSellableBuildings);
    connect(buildDialog->getBuildBuildingDialog(), &BuildBuildingDialog::sellBuildings, game->getBoard(), &Board::sellBuildings);


    foreach(SpaceView* space, spaces)
    {
        connect(game->getBoard(), &Board::buildingsAreBuilded, this, &BoardView::buildBuildings);
    }
}

void BoardView::connectPropertySpaces()
{
    QList<Space*> spaces = game->getBoard()->getSpaces();

    foreach(Space* space, spaces)
    {
        if (space->getType() == Space::Type::STREET)
        {
            StreetSpace* streetSpace = (StreetSpace*)space;
            connect(streetSpace, SIGNAL(streetIsBuyable(QString,int,int,int,int,int,int,int,int,int,int, bool, int)), buyDialog, SLOT(showDialog(QString,int,int,int,int,int,int,int,int,int,int, bool, int)));
            connect(streetSpace, SIGNAL(rentPaid(int,int)), rentDialog, SLOT(showDialog(int,int)));
        }
        else if (space->getType() == Space::Type::COMPANY)
        {
            CompanySpace* companySpace = (CompanySpace*)space;
            connect(companySpace, SIGNAL(companyIsBuyable(QString,int,int, bool, int)), buyDialog, SLOT(showDialog(QString,int,int, bool, int)));
            connect(companySpace, SIGNAL(rentPaid(int,int)), rentDialog, SLOT(showDialog(int,int)));
        }
        else if (space->getType() == Space::Type::STATION)
        {
            StationSpace* stationSpace = (StationSpace*)space;
            connect(stationSpace, SIGNAL(stationIsBuyable(QString,int,int,int, bool, int)), buyDialog, SLOT(showDialog(QString,int,int,int, bool,int)));
            connect(stationSpace, SIGNAL(rentPaid(int,int)), rentDialog, SLOT(showDialog(int,int)));
        }
    }
}

void BoardView::connectJailDialog()
{
    connect(game->getBoard(), SIGNAL(inJailRolled(bool,int,int)), jailDialog, SLOT(showRollMessage(bool,int,int)));
    connect(game->getBoard(), SIGNAL(inJailCardUsed()), jailDialog, SLOT(showjailCardMessage()));
    connect(game->getBoard(), SIGNAL(inJailPaid()), jailDialog, SLOT(showPayMessage()));
    connect(jailDialog, SIGNAL(payButtonClicked()), game->getBoard(), SLOT(inJailPay()));
    connect(jailDialog, SIGNAL(rollButtonClicked()), game->getBoard(), SLOT(inJailRoll()));
    connect(jailDialog, SIGNAL(jailCardButtonClicked()), game->getBoard(), SLOT(inJailUseCard()));
    connect(game->getBoard(), SIGNAL(isInJail(bool)), jailDialog, SLOT(showDialog(bool)));

}

void BoardView::connectCommunityChest()
{
    QList<CommunityChestCard*> cards = game->getBoard()->getCommunityChestCards();

    foreach(CommunityChestCard* card, cards)
    {
        connect(card, SIGNAL(usedCard(QString,int)), this, SLOT(showCommunityChestMessage(QString,int)));
    }
}

void BoardView::connectPlayers()
{
    QList<Player*> players = game->getBoard()->getPlayers();

    foreach(Player* player, players)
    {
        connect(player, SIGNAL(notEnoughMoney()), this, SLOT(showNotEnoughMoneyMessage()));
    }
}

void BoardView::getNumberPlayers(int numberPlayers)
{
    game = new Game(numberPlayers);
    QList<Player*> playerList = game->getBoard()->getPlayers();

    for (int i = 0; i < numberPlayers; i++)
    {
        playerInfo.append(new PlayerInfoView(i, playerList[i]->getColour(), 2500,1000,60*(i+1)));
        addItem(playerInfo[i]);

        players.append(new PlayerView(i,playerList[i]->getColour()));
        players[i]->move(spaces[0]);

        // connect move Player-PlayerView
        connect((game->getBoard())->getPlayers()[i], SIGNAL(moved(int,int)), this, SLOT(movePlayer(int,int)));
        connect((game->getBoard())->getPlayers()[i], &Player::moneyChanged, playerInfo[i], &PlayerInfoView::setMoney);
        connect(playerInfo[i], &PlayerInfoView::clicked, this, &BoardView::showPlayerProperties);

        if (i != 0)
            playerInfo[i]->setOpacity(0.33);
    }
    amountPlayerDialog->close();

}

/*
 * Moves the given player to a given position
 * 2 arguments: given player, position
 */
void BoardView::movePlayer(int currentPlayer, int position)
{
    players[currentPlayer]->move(spaces[position]);
    endTurnButton->setEnabled(true);
    rollButton->setEnabled(false);

}

void BoardView::selectBusTicketSpaces(int currentPosition, int endPosition)
{
    int i = currentPosition + 1;

    while(i != (endPosition + 1))
    {
        spaces[i]->setFlag(QGraphicsItem::ItemIsSelectable);
        i = (i + 1) % SIZE_OF_BOARD;
    }
}

/* Author: Sebastiaan
 * Enables the Bus Ticket button
 */
void BoardView::showBusTicketButton()
{
    busTicketButton->setEnabled(true);
}

/* Author: Sebastiaan
 * Shows that the bus ticket has been used
 */
void BoardView::useBusTicket()
{
    QMessageBox *howToMessage = new QMessageBox();
    howToMessage->setDefaultButton(QMessageBox::Ok);
    howToMessage->setWindowTitle("Busticket");
    howToMessage->setText("You are using a busticket.\nSelect any space on your side.");
    howToMessage->exec();
    busTicketButton->setEnabled(false);

    rollButton->setEnabled(false);
}

void BoardView::moveToAnySpace()
{
    changeSelectable(true);

    QMessageBox *anySpaceMessage = new QMessageBox();
    anySpaceMessage->setDefaultButton(QMessageBox::Ok);
    anySpaceMessage->setWindowTitle("Move to any space");
    anySpaceMessage->setText("You rolled a triple.\nYou can select any space on the board you want to move to.");
    anySpaceMessage->exec();
}

void BoardView::rollAgain()
{
    QMessageBox *rollAgainMessage = new QMessageBox();
    rollAgainMessage->setDefaultButton(QMessageBox::Ok);
    rollAgainMessage->setWindowTitle("Roll again");
    rollAgainMessage->setText("You rolled a double.\nYou can roll the dice again.");
    rollAgainMessage->exec();

    rollButton->setEnabled(true);
}

void BoardView::showCommunityChestMessage(QString description, int value)
{
    QMessageBox *communityChestMessage = new QMessageBox();
    communityChestMessage->setDefaultButton(QMessageBox::Ok);
    communityChestMessage->setWindowTitle("Special card");

    if (value == 0)
    {
        communityChestMessage->setText(description);
    }
    else
    {
        if(value < 0)
        {
            communityChestMessage->setText(description + "\nYou have to pay " + QString::number(abs(value)) + ".");
        }
        else
        {
            communityChestMessage->setText(description + "\nYou get " + QString::number(abs(value)) + ".");
        }
    }

    communityChestMessage->exec();
}

void BoardView::showNotEnoughMoneyMessage()
{
    QMessageBox *notEnoughMessage = new QMessageBox();
    notEnoughMessage->setDefaultButton(QMessageBox::Ok);
    notEnoughMessage->setWindowTitle("Not enough money.");
    notEnoughMessage->setText("You don't have enough money to afford this. Sell properties or buildings.");
    notEnoughMessage->exec();
}

void BoardView::showBrokeMessage(int numberPlayer)
{
    QMessageBox *brokeMessage = new QMessageBox();
    brokeMessage->setDefaultButton(QMessageBox::Ok);
    brokeMessage->setWindowTitle("Broke.");
    brokeMessage->setText("Your total balance (Mortgage values of properties and buildingprices) is less than the amount you have to pay."
                          "\nYou're officially broke and getting retired from the game.");
    brokeMessage->exec();

    emit playerRetired();
}

/*  Author: Ho Yuet
 *  shows the property of the clicked player
 */
void BoardView::showPlayerProperties(int numberPlayer)
{
    int currentTurn = game->getBoard()->getCurrentTurn();
    QList<PropertyCard*>cards = (game->getBoard())->getPlayers()[numberPlayer]->getProperties();
    propertyDialog->getProperties(cards, currentTurn, numberPlayer);
}

/*  Author: Ho Yuet
 *  Makes it able to see who the current player is
 */
void BoardView::turnSwitched(int currentPlayer)
{
    //makes the current player visible
    foreach(PlayerInfoView* info, playerInfo)
    {
        if (info->getNumberPlayer() == currentPlayer)
            info->setOpacity(1);
        else
            info->setOpacity(0.33);
    }

    rollButton->setEnabled(true);
    endTurnButton->setEnabled(false);
}

/*  Author: Ho Yuet
 *  Show on board who has bought what
 */
void BoardView::propertyHasBeenBought(int player, QColor colour, int space)
{
    spaces[space]->changeOwner(player, colour);
}

/*  Author: Ho Yuet
 * Builds the buildings from the given position, type building and amount of buildings
 */
void BoardView::buildBuildings(int indexPosition, PropertyCard::TypeBuilding building, int amount)

{
    spaces[indexPosition]->setBuildings(building, amount);
}

void BoardView::showMoneyMessage(int amount)
{
    QMessageBox *moneyMessage = new QMessageBox();
    moneyMessage->setDefaultButton(QMessageBox::Ok);
    moneyMessage->setWindowTitle("Money");

    if (amount < 0)
    {
        moneyMessage->setText("Not so lucky! Pay " + QString::number(abs(amount)) + " to the bank.");
    }
    else
    {
        moneyMessage->setText("It's your lucky day! You get " + QString::number(amount) + " from the bank.");
    }

    moneyMessage->exec();
}

void BoardView::showToJailMessage()
{
    QMessageBox *jailMessage = new QMessageBox();
    jailMessage->setDefaultButton(QMessageBox::Ok);
    jailMessage->setWindowTitle("Go to jail");
    jailMessage->setText("Not so lucky. You've been sent to jail.\n\n Pay 50£ or roll doubles within your 3 next turns\n or use a 'Get-Out-Of-Jail' card");
    jailMessage->exec();
}

/*Author: Ho Yuet
 * Updates View after loading
 */
void BoardView::justLoaded(int amountPlayers)
{
    for (int i =0; i < players.count(); i++)  // remove the old players (view)
    {
        players[i]->hide();
        playerInfo[i]->hide();
        delete players[i];
        delete playerInfo[i];
    }
    if (!players.isEmpty())
        players.clear();
    if (!playerInfo.isEmpty())
        playerInfo.clear();

    removeAllSpaceOwners();

    QList<Player*> playerList = (game->getBoard())->getPlayers();
    int currentTurn = (game->getBoard())->getCurrentTurn();

    for (int i = 0; i < amountPlayers; i++)
    {
        if (playerList[i] != NULL)  // if the player hasnt lost yet (is not null)
        {
            playerInfo.append(new PlayerInfoView(i, playerList[i]->getColour(), 2500,1000,60*(i+1)));
            addItem(playerInfo[i]);
            players.append(new PlayerView(i,(playerList[i]->getColour())));
            players[i]->move(spaces[playerList[i]->getCurrentPosition()]);

            // connect move Player-PlayerView
            connect((game->getBoard())->getPlayers()[i], SIGNAL(moved(int,int)), this, SLOT(movePlayer(int,int)));
            connect((game->getBoard())->getPlayers()[i], &Player::moneyChanged, playerInfo[i], &PlayerInfoView::setMoney);
            connect(playerInfo[i], &PlayerInfoView::clicked, this, &BoardView::showPlayerProperties);

            playerList[i]->changeMoney(0);
            if (i != currentTurn)
                playerInfo[i]->setOpacity(0.33);
        }

    }



}

/* Author: Ho Yuet
 * removes all OwnerViews
 */
void BoardView::removeAllSpaceOwners()
{
    foreach(SpaceView* space, spaces)
    {
        space->removeOwner();
        // delete all buildings
        QList<QGraphicsItem*>items = space->childItems();
        foreach(QGraphicsItem* item, items)
        {
            item->hide();
            delete item;
        }
    }
}

/*  Author: Ho Yuet
 * Shows saved game message
 */
void BoardView::savedSuccessfully()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Save game");
    msgBox.setText("Saved successfully!");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
}

/*  Author: Ho Yuet
 *  Shows an error message if you can't build a building
 */
void BoardView::showBuilingErrorMessage()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Error Building");
    msgBox.setText("Unable to build buildings (Check if there is a mortgaged property)");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
}

/*  Author: Ho Yuet
 *  Shows an error message if you can't mortgage
 */
void BoardView::showMortgageErrorMessage()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Error Mortgage");
    msgBox.setText("Unable to mortgage(Check if there are buildings built on the property)");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
}





