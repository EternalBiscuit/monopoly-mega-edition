// Author: Sebastiaan, Ho Yuet
#include "mainwindow.h"
#include "boardview.h"
#include "board.h"

#include <QGraphicsView>
#include <QGridLayout>
#include <QPushButton>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    boardScene = new BoardView();
    view = new QGraphicsView(boardScene);   // Set boardScene as current view
    view->setSceneRect(0,0,1280,720);
    setCentralWidget(view);

}

MainWindow::~MainWindow()
{

}
