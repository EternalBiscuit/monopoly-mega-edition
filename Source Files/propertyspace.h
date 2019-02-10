#ifndef PROPERTYSPACE_H
#define PROPERTYSPACE_H
#include "space.h"
#include <QColor>
class PropertySpace: public Space
{
public:
    PropertySpace();
    PropertySpace(int newPrice, QString newName, QColor newColour);
    int getOwner();
    bool checkIfOwned();
    QString getName();
    void hasOwnership();
    void newOwner(int ownerNumber);
    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;
    virtual void doAuction(Board& board) = 0;
protected:
    int price;
    QString name;
    QColor colour;
    int owner;
    bool isOwned;
};

#endif // PROPERTYSPACE_H

