// Author: Sebastiaan
#ifndef SPEEDDICE_H
#define SPEEDDICE_H

#include "dice.h"

class QString;

class SpeedDice : public Dice
{
    Q_OBJECT
public:
    SpeedDice();
    QList<QString> SpeedDiceSymbols {"1", "2", "3", "MONOPOLY", "MONOPOLY", "BUS"};

    void rollDice();
    QString getRolledSymbol();
    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;
};

#endif // SPEEDDICE_H

