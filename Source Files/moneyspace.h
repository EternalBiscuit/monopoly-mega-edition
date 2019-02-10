#ifndef MONEYSPACE_H
#define MONEYSPACE_H
#include "specialspace.h"

class MoneySpace: public SpecialSpace
{
    Q_OBJECT
public:
    MoneySpace(int newValue=0);
    int getValue()const;
    void doSpaceMove(Board& board);
    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;
protected:
    int value;
signals:
    void moneyChanged(int amount);
};

#endif // MONEYSPACE_H

