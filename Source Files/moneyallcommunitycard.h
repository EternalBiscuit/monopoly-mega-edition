#ifndef MONEYALLCOMMUNITYCARD_H
#define MONEYALLCOMMUNITYCARD_H

#include "communitychestcard.h"


class MoneyAllCommunityCard : public CommunityChestCard
{
    Q_OBJECT
public:
    MoneyAllCommunityCard(QString newDescription, int newValue);
    void useCard(Board& board);



};

#endif // MONEYALLCOMMUNITYCARD_H
