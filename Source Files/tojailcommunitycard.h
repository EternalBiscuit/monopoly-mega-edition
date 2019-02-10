#ifndef TOJAILCOMMUNITYCARD_H
#define TOJAILCOMMUNITYCARD_H

#include "communitychestcard.h"


class ToJailCommunityCard : public CommunityChestCard
{
    Q_OBJECT
public:
    ToJailCommunityCard(QString newDescription);
    void useCard(Board& board);

};

#endif // TOJAILCOMMUNITYCARD_H
