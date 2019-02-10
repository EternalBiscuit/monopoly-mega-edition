#ifndef GOTOJAILSPACE_H
#define GOTOJAILSPACE_H
#include "specialspace.h"

class GoToJailSpace: public SpecialSpace
{
public:
    GoToJailSpace();
    void doSpaceMove(Board& board);
void read(const QJsonObject &json);
    void write(QJsonObject &json) const;

};

#endif // GOTOJAILSPACE_H
