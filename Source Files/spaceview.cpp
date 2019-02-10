// Author: Ho Yuet
#include "spaceview.h"
#include "ownerview.h"
#include <QColor>
#include <QBrush>
#include <buildingview.h>
#include <QDebug>

/*
 * Constructor of SpaceView
 * 5 arguments: x position, y position, width, height, rotation
 */
SpaceView::SpaceView(int posX, int posY, int width, int height, int rotation, int newSpaceIndex)
{
    setRect(0,0,width, height);
    setPos(posX,posY);
    setTransformOriginPoint(width/2, height/2);
    setRotation(rotation);
    spaceIndex = newSpaceIndex;
    owner = NULL;
    //setFlag(ItemIsSelectable);
}

int SpaceView::getSpaceIndex()
{
    return spaceIndex;
}

/*
 * Builds the given building with the amount
 */
void SpaceView::setBuildings(PropertyCard::TypeBuilding building, int amount)
{
    //remove old buildings
    for(int i = 0; i < buildings.count(); i++)
    {
        buildings[i]->hide();
        delete buildings[i];
    }
    buildings.clear();

    //build the buildings
    for(int i =0; i < amount; i++)
    {
        buildings.append(new BuildingView(this));
        buildings[i]->setParentItem(this);
        // build the correct building
        switch (building) {
        case PropertyCard::TypeBuilding::HOUSE:
            buildings[i]->buildHouse();
            break;
        case PropertyCard::TypeBuilding::HOTEL:
            buildings[i]->buildHotel();
            break;
        case PropertyCard::TypeBuilding::SKYSCRAPER:
            buildings[i]->buildSkyscraper();
            break;
        case PropertyCard::TypeBuilding::RAILDEPOT:
            buildings[i]->buildRailDepot();
            break;
        default:
            break;
        }
        buildings[i]->setPos(i*10,0);
    }
}

/*
 * Changes the owner of the space
 */
void SpaceView::changeOwner(int player, QColor colour)
{
    if (owner == NULL)
        owner = new OwnerView(this, player+1, colour);
    else
        owner->switchOwner(player+1, colour);
}

/*c
 * Removes the owner if possible
 */
void SpaceView::removeOwner()
{
    if (owner != NULL)
    {
        owner->hide();
        delete owner;
        owner = NULL;
    }

}


