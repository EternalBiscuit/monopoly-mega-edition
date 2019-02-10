#ifndef COMMUNITYCHESTSPACE_H
#define COMMUNITYCHESTSPACE_H
#include "cardspace.h"

class CommunityChestSpace: public CardSpace
{
public:
    CommunityChestSpace();
    void doSpaceMove(Board& board);
    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;


};

#endif // COMMUNITYCHESTSPACE_H
