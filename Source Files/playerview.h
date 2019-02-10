// Author: Ho Yuet
#ifndef PLAYERVIEW_H
#define PLAYERVIEW_H
#include <QColor>
#include <QGraphicsEllipseItem>
#include <QObject>


class PlayerView: public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    PlayerView(int newNumPlayer, QColor newColour);
public slots:
    void move(QGraphicsItem* parent);   // switches the parent
private:
    QColor colour;
    int numPlayer;
};

#endif // PLAYERVIEW_H
