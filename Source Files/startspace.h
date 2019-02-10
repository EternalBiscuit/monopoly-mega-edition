#ifndef STARTSPACE_H
#define STARTSPACE_H
#include "moneyspace.h"

class StartSpace: public SpecialSpace
{
    Q_OBJECT
public:
    StartSpace();
    void doSpaceMove(Board& board);
    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;
};

#endif // STARTSPACE_H

