// Author: Ho Yuet
#include "buildingview.h"
#include <QBrush>

BuildingView::BuildingView(QGraphicsItem* parent)
{
    setRect(0,0,10,10);
    setParentItem(parent);

}

//Build buildings accordign to colour
void BuildingView::buildHouse()
{
    setBrush(QBrush(QColor(0,255,0)));  // green
}

void BuildingView::buildHotel()
{
    setBrush(QBrush(QColor(255,0,0))); // red
}

void BuildingView::buildSkyscraper()
{
    setBrush(QBrush(QColor(238,130,238))); //purple
}

void BuildingView::buildRailDepot()
{
    setBrush(QBrush(QColor(212,175,55))); // gold
}
