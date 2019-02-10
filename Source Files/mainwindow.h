// Author: Sebastiaan, Ho Yuet
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class BoardView;
class QGraphicsView;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    BoardView* boardScene;
    QGraphicsView* view;

};

#endif // MAINWINDOW_H
