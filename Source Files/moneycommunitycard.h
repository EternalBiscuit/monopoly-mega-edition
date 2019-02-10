#ifndef MONEYCOMMUNITYCARD_H
#define MONEYCOMMUNITYCARD_H

#include "communitychestcard.h"


class MoneyCommunityCard : public CommunityChestCard
{
    Q_OBJECT
public:
    MoneyCommunityCard(QString newDescription, int newValue);
    void useCard(Board& board);

};

#endif // MONEYCOMMUNITYCARD_H
