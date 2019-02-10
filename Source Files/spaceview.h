// Author: Ho Yuet
#ifndef SPACEVIEW_H
#define SPACEVIEW_H
#include <QGraphicsRectItem>
class BuildingView;
class OwnerView;
#include "propertycard.h"
#include "board.h"

class SpaceView: public QGraphicsRectItem
{
public:
    SpaceView(int posX, int posY, int width, int height, int rotation, int newSpaceIndex);
    int getSpaceIndex();
    void setBuildings(PropertyCard::TypeBuilding building, int amount);
    void changeOwner(int player, QColor colour);
private:
    int spaceIndex;
    QList<BuildingView*> buildings;
    OwnerView* owner;
public slots:
    void removeOwner();


};

#endif // SPACEVIEW_H

