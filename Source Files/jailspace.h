#ifndef JAILSPACE_H
#define JAILSPACE_H
#include "specialspace.h"

class JailSpace: public SpecialSpace
{
public:
    JailSpace();
    void doSpaceMove(Board& board);
    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;
};

#endif // JAILSPACE_H

