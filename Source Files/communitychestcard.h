#ifndef COMMUNITYCHESTCARD_H
#define COMMUNITYCHESTCARD_H

#include "specialcard.h"

class Board;


class CommunityChestCard : public SpecialCard
{
    Q_OBJECT
public:
    CommunityChestCard(QString newDescription, int newValue = 0);
    virtual void useCard(Board& board) = 0;
protected:
    QString description;
    int value;
signals:
    void usedCard(QString description, int value);

};

#endif // COMMUNITYCHESTCARD_H
