#ifndef BUSCARD_H
#define BUSCARD_H

#include "card.h"

class BusCard : public Card
{
public:
    BusCard();
    void useCard();
};

#endif // BUSCARD_H
