#include "playerview.h"
#include <QGraphicsSimpleTextItem>
#include <QBrush>

/*
 * Constructor of PlayerView
 * 2 arguments: number of player, colour
 */
PlayerView::PlayerView(int newNumPlayer, QColor newColour)
{
    colour = newColour;
    numPlayer = newNumPlayer + 1;
    setRect(0,10,16,16);
    setBrush(QBrush(colour));

    QGraphicsSimpleTextItem* numPlayerText = new QGraphicsSimpleTextItem;
    numPlayerText->setPos(5,10);
    numPlayerText->setText(QString::number(numPlayer));
    numPlayerText->setParentItem(this);
}

/*
 * Switches the parent of the PlayerView
 * 1 argument: parent (QGraphicsItem*)
 */
void PlayerView::move(QGraphicsItem *parent)
{
    setParentItem(parent);
    int xPos = ((numPlayer - 1) % 3) * 16;
    int yPos = ((numPlayer - 1) / 3) * 16;
    setPos(xPos, yPos);

}
