#ifndef CHANCESPACE_H
#define CHANCESPACE_H
#include "cardspace.h"

class ChanceSpace: public CardSpace
{
public:
    ChanceSpace();
    void doSpaceMove(Board& board);
    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;
};

#endif // CHANCESPACE_H

