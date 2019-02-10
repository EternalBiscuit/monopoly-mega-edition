// Author: Sebastiaan
#include "game.h"
#include "board.h"
#include <qdebug.h>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>
#include <QJsonDocument>
#include <QDir>
#include <QDesktopServices>
#include <QFileDialog>

Game::Game(int numberPlayers)
{
    board = new Board(numberPlayers);
}

void Game::loadGame()
{
    QString path = QFileDialog::getOpenFileName();
    QDesktopServices::openUrl(QDir::currentPath());
    QFile loadFile(path);

    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open load file.");
        return;
    }

    QByteArray saveData = loadFile.readAll();

    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

    read(loadDoc.object());
}

void Game::saveGame() const
{

    QString path = QFileDialog::getOpenFileName();
    QDesktopServices::openUrl(QDir::currentPath());

    QFile saveFile(path);
    if (!saveFile.open(QIODevice::WriteOnly))
    {
        qWarning("Couldn't open save file.");
        return;
    }
    QJsonObject gameObject;
    write(gameObject);
    QJsonDocument saveDoc(gameObject);
    saveFile.write(saveDoc.toJson());
    emit saved();
}


void Game::playGame()
{

}

Board *Game::getBoard()
{
    return board;
}

/*  Author: Ho Yuet
 * load
 */
void Game::read(const QJsonObject &json)
{
    board->read(json["board"].toObject());
}

/*Author: Ho Yuet
 * save
 */
void Game::write(QJsonObject &json) const
{
    QJsonObject boardObject;
    board->write(boardObject);

    json["board"] = boardObject;
}

