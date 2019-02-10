// Author: Ho Yuet
#ifndef PLAYERINFOVIEW_H
#define PLAYERINFOVIEW_H

#include <QGraphicsRectItem>

class QScrollArea;
class QGraphicsSimpleTextItem;
class PropertiesDialog;

class PlayerInfoView: public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    PlayerInfoView(int newNumPlayer, QColor newColour, int newMoney, int posX, int posY);
    int getNumberPlayer();
private:
    int amountMoney;
    int numPlayer;
    QColor colour;
    QScrollArea* property;
    QGraphicsSimpleTextItem* moneyText;
    void mousePressEvent(QGraphicsSceneMouseEvent *event);  // on press show players property
public slots:
    void setMoney(int newMoney);    // sets the new amount of money
signals:
    void clicked(int numPlayer);
};

#endif // PLAYERINFOVIEW_H
