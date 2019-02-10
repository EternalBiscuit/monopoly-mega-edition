#include "gotojailspace.h"
#include "board.h"
#include <QJsonObject>

GoToJailSpace::GoToJailSpace()
{
    type = TOJAIL;
}

void GoToJailSpace::doSpaceMove(Board& board)
{
    board.goToJail();
}

/*
 * Load
 */
void GoToJailSpace::read(const QJsonObject &json)
{
    type = Type(qRound(json["type"].toDouble()));
}

/*
 * Save
 */
void GoToJailSpace::write(QJsonObject &json) const
{
    json["type"] = type;
}

