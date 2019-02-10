#ifndef TOGOCOMMUNITYCARD_H
#define TOGOCOMMUNITYCARD_H

#include "communitychestcard.h"


class ToGoCommunityCard : public CommunityChestCard
{
    Q_OBJECT
public:
    ToGoCommunityCard(QString newDescription);
    void useCard(Board& board);

};

#endif // TOGOCOMMUNITYCARD_H
