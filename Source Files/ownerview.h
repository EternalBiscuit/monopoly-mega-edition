#ifndef OWNERVIEW_H
#define OWNERVIEW_H
#include <QGraphicsRectItem>

class OwnerView: public QGraphicsRectItem
{
public:
    OwnerView(QGraphicsItem* parent,int player, QColor newColour);
public slots:
    void switchOwner(int newNumberPlayer, QColor newColour);
private:
    QColor colour;
    QGraphicsSimpleTextItem* numberPlayer;

};

#endif // OWNERVIEW_H
