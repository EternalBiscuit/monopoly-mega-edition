// Author: Ho Yuet
#ifndef BUILDINGVIEW_H
#define BUILDINGVIEW_H
#include <QGraphicsRectItem>

class BuildingView: public QGraphicsRectItem
{
public:
    BuildingView(QGraphicsItem* parent);
    //changes the colour of the building
    void buildHouse();
    void buildHotel();
    void buildSkyscraper();
    void buildRailDepot();
private:

};

#endif // BUILDINGVIEW_H
