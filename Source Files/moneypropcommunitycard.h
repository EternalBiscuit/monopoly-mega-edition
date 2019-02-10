#ifndef MONEYPROPCOMMUNITYCARD_H
#define MONEYPROPCOMMUNITYCARD_H

#include "communitychestcard.h"


class MoneyPropCommunityCard : public CommunityChestCard
{
    Q_OBJECT
public:
    MoneyPropCommunityCard(QString newDescription);
    void useCard(Board& board);
private:
    static const int HOTEL_COST = 115;
    static const int HOUSE_COST = 40;


};

#endif // MONEYPROPCOMMUNITYCARD_H
