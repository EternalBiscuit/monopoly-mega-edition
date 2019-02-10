#include "ownerview.h"
#include <QBrush>

OwnerView::OwnerView(QGraphicsItem* parent, int player, QColor newColour)
{
    numberPlayer = new QGraphicsSimpleTextItem(this);
    numberPlayer->setText(QString::number(player+1));
    numberPlayer->setPos(3,1);
    colour = newColour;
    setRect(0,0,15,15);
    setBrush(colour);
    setParentItem(parent);
    if (parent->rotation() == 0)
        setPos(0,60);
    else if (parent->rotation() == 90)
        setPos(0,94);
    else if(parent->rotation() == 180)
        setPos(0,61);
    else if(parent->rotation() == 270)
        setPos(0,82);

}

void OwnerView::switchOwner(int newNumberPlayer, QColor newColour)
{
    numberPlayer->setText(QString::number(newNumberPlayer));
    colour = newColour;
    setBrush(colour);

}
