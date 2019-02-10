#ifndef CARDSPACE_H
#define CARDSPACE_H
#include "space.h"

class Card;

class CardSpace: public Space
{
public:
    CardSpace();
    void doSpaceMove(Board& board);
    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;
    //Card* takeCard();
};

#endif // CARDSPACE_H

