// Author: Sebastiaan
#include "speeddice.h"
#include <time.h>

/*
 * Constructor of SpeedDice
 */
SpeedDice::SpeedDice()
{
    type = SPEEDDICE;
}

/*
 *  Rolls rolls the speed dice
 */
void SpeedDice::rollDice()
{
    srand(time(NULL));

    rolledNumber = rand() % (MAXPIP);

    rolledSymbol = SpeedDiceSymbols[rolledNumber];
}

QString SpeedDice::getRolledSymbol()
{
    return rolledSymbol;
}

/*  Author: Ho Yuet
 * Load
 */
void SpeedDice::read(const QJsonObject &json)
{
    Dice::read(json);
}

/*  Author: Ho Yuet
 * Save
 */
void SpeedDice::write(QJsonObject &json) const
{
    Dice::write(json);
}

