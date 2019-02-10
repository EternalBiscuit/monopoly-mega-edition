// Author: Ho Yuet
#ifndef COMPANYSPACE_H
#define COMPANYSPACE_H
#include "propertyspace.h"
#include <QColor>

class CompanySpace: public PropertySpace
{
    Q_OBJECT
public:
    CompanySpace();
    CompanySpace(int newValue, QString newName, QColor newColor);
    void doSpaceMove(Board& board);
    void doAuction(Board& board);
void read(const QJsonObject &json);
    void write(QJsonObject &json) const;

signals:
    void companyIsBuyable(QString companyName, int price, int priceMortgage, bool auction, int spaceIndex);
    void rentPaid(int rent, int owner)const;

};

#endif // COMPANYSPACE_H
