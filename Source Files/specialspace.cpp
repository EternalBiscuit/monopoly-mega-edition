#include "specialspace.h"
#include <QJsonObject>

SpecialSpace::SpecialSpace()
{

}

/*
 * Load
 */
void SpecialSpace::read(const QJsonObject &json)
{

    type = Type(qRound(json["type"].toDouble()));
}

/*
 * load
 */
void SpecialSpace::write(QJsonObject &json) const
{
    json["type"] = type;
}

