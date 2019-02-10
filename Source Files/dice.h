// Author: Sebastiaan
#ifndef DICE_H
#define DICE_H

#include "stdlib.h"
#include <QList>
#include <QString>
#include <QObject>

class Dice : public QObject
{
    Q_OBJECT
public:
    enum TypeDice{DICE,SPEEDDICE};
    Dice();
    virtual void rollDice();
    QString getRolledSymbol();
    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;
protected:
    static const int MAXPIP = 6;
    QString rolledSymbol;
    int rolledNumber;
    TypeDice type;
signals:
    void rolled();
};

#endif // DICE_H

