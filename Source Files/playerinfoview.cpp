#include "playerinfoview.h"
#include "propertiesdialog.h"
#include <QGraphicsSimpleTextItem>
#include <QBrush>
#include <QDialog>
#include <QDebug>

/*
 *  Constructor of PlayerInfoView
 *  5 arguments: number of the player, colour, amount of money, x position, y position
 */
PlayerInfoView::PlayerInfoView(int newNumPlayer,QColor newColour, int newMoney, int posX, int posY)
{
    numPlayer = newNumPlayer;
    amountMoney = newMoney;
    colour = newColour;

    setRect(0, 0, 185,50);
    setBrush(QBrush(colour));

    // show which player
    QGraphicsSimpleTextItem* numPlayerText = new QGraphicsSimpleTextItem;
    numPlayerText->setParentItem(this);
    numPlayerText->setPos(5,1);
    numPlayerText->setText("Player " + QString::number(numPlayer+1));
    numPlayerText->show();

    // show the label "Money"
    QGraphicsSimpleTextItem* moneyLabel = new QGraphicsSimpleTextItem;
    moneyLabel->setParentItem(this);
    moneyLabel->setPos(5,25);
    moneyLabel->setText("Money: ");
    moneyLabel->show();

    // shows current amount of money
    moneyText = new QGraphicsSimpleTextItem;
    moneyText->setPos(100,25);
    moneyText->setText(QString::number(amountMoney));
    moneyText->show();
    moneyText->setParentItem(this);

    setPos(posX, posY);
}

/*
 * returns the number of the player
 */
int PlayerInfoView::getNumberPlayer()
{
    return numPlayer;
}

/*
 * On click: show properties of the player
 */
void PlayerInfoView::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    // create new window/ dialog to show properties
    emit clicked(numPlayer);

    QGraphicsRectItem::mousePressEvent(event);
}

/*
 * Sets a new amount of money
 * 1 argument: the new amount of money
 */
void PlayerInfoView::setMoney(int newMoney)
{
    amountMoney = newMoney;
    moneyText->setText(QString::number(amountMoney));
}
