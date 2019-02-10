// Author: Ho Yuet
#ifndef SPACE_H
#define SPACE_H
#include <QObject>

class Board;

class Space: public QObject
{
public:
    enum Type{START, CHEST, CHANCE, STREET, MONEY, JAIL, BUS, SPECIAL, COMPANY, STATION, AUCTION, TOJAIL};
    Space();
    virtual void doSpaceMove(Board& board) = 0; // pure function for polymorfism
    Type getType();
    virtual void read(const QJsonObject &json) = 0;
    virtual void write(QJsonObject &json) const = 0;
protected:
    Type type;
};

#endif // SPACE_H

