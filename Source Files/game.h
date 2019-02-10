// Author: Sebastiaan
#ifndef GAME_H
#define GAME_H

#include <QString>
#include "player.h"
#include <QObject>

class Board;

class Game : public QObject
{
    Q_OBJECT
public:
    Game(int numberPlayers);
    void playGame();
    Board* getBoard();
    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;
public slots:
    void loadGame();
    void saveGame()const;
private:
    Board* board;
signals:
    void saved()const;
};

#endif // GAME_H

