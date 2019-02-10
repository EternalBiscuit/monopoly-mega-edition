#ifndef OUTOFJAILCOMMUNITYCARD_H
#define OUTOFJAILCOMMUNITYCARD_H

#include "communitychestcard.h"


class OutOfJailCommunityCard : public CommunityChestCard
{
    Q_OBJECT
public:
    OutOfJailCommunityCard(QString newDescription);
    void useCard(Board& board);

};

#endif // OUTOFJAILCOMMUNITYCARD_H
