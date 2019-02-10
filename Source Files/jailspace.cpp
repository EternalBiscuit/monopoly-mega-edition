#include "jailspace.h"
#include <QJsonObject>


JailSpace::JailSpace()
{
    type = JAIL;
}

void JailSpace::doSpaceMove(Board& board)
{

}

/*
 * Load
 */
void JailSpace::read(const QJsonObject &json)
{
    type = Type(qRound(json["type"].toDouble()));
}

/*
 * Save
 */
void JailSpace::write(QJsonObject &json) const
{
    json["type"] = type;
}

