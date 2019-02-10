#include "moneyspace.h"
#include "board.h"
#include <QJsonObject>

MoneySpace::MoneySpace(int newValue)
{
    value = newValue;
    type = MONEY;
}

int MoneySpace::getValue() const
{
    return value;
}

void MoneySpace::doSpaceMove(Board& board)
{
    board.doTransaction(value);
    emit moneyChanged(value);
}

/*
 * Load
 */
void MoneySpace::read(const QJsonObject &json)
{
    type = Type(qRound(json["type"].toDouble()));
    value = json["value"].toInt();
}

/*
 * Save
 */
void MoneySpace::write(QJsonObject &json) const
{
    json["type"] = type;
    json["value"] = value;
}

