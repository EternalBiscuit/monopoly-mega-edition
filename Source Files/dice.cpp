// Author: Sebastiaan
#include "dice.h"
#include <time.h>
#include <QJsonObject>

Dice::Dice()
{
    type = DICE;
}

QString Dice::getRolledSymbol()
{
    return rolledSymbol;
}

/*  Author: Ho Yuet
 * Load
 */
void Dice::read(const QJsonObject &json)
{
    type = (TypeDice)qRound(json["type"].toDouble());
    rolledNumber = json["rolledNumber"].toInt();
    rolledSymbol = json["rolledSymbol"].toString();
}


/*  Author: Ho Yuet
 * Save
 */
void Dice::write(QJsonObject &json) const
{
    json["type"] = type;
    json["rolledNumber"] = rolledNumber;
    json["rolledSymbol"] = rolledSymbol;
}

void Dice::rollDice()
{
    rolledNumber = rand() % MAXPIP + 1;

    rolledSymbol = QString::number(rolledNumber);

}
