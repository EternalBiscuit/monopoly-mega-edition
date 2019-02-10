// Author: Ho Yuet
#include "monopolyboardview.h"
#include <QPixmap>

#include "boardview.h"

/*
 * Constructor of MonopolyBoardView
 */
MonopolyBoardView::MonopolyBoardView()
{
    setPixmap(QPixmap(":/images/MonopolyBoard.png"));   // sets the correct monopoly image

}
