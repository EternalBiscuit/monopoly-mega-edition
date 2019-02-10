// Author: Sebastiaan
#include "dicedialog.h"
#include <QGridLayout>
#include <QMessageBox>

/*
 * Constructor of DiceDialog
 */
DiceDialog::DiceDialog(QWidget* parent)
    : QDialog(parent)
{

    QLabel* firstDice = new QLabel(tr("First dice: "));
    QLabel* secondDice = new QLabel(tr("Second dice: "));
    QLabel* thirdDice = new QLabel(tr("Speed dice: "));

    closeButton = new QPushButton(tr("Close"));
    closeButton->setDefault(true);

    firstDiceResult = new QLabel();
    secondDiceResult = new QLabel();
    thirdDiceResult = new QLabel();

    busButton = new QPushButton(this);
    busButton->setText("Bus Ticket");

    chanceButton = new QPushButton(this);
    chanceButton->setText("Chance/Community Chest");

    layout = new QGridLayout;
    layout->addWidget(firstDice, 0, 0);
    layout->addWidget(secondDice, 0, 1);
    layout->addWidget(thirdDice, 0, 2);
    layout->addWidget(firstDiceResult, 1, 0);
    layout->addWidget(secondDiceResult, 1, 1);
    layout->addWidget(thirdDiceResult, 1, 2);
    layout->addWidget(busButton, 2, 0);
    layout->addWidget(chanceButton, 2, 1);
    layout->addWidget(closeButton, 2, 2);

    this->setLayout(layout);

    this->setWindowTitle(tr("Dice results"));

    connect(closeButton, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(busButton, SIGNAL(clicked(bool)), this, SIGNAL(busTicketChosen()));
    connect(busButton, SIGNAL(clicked(bool)), this, SLOT(hideBusButtons()));
    connect(chanceButton, SIGNAL(clicked(bool)), this, SLOT(hideBusButtons()));
    connect(chanceButton, SIGNAL(clicked(bool)), this, SIGNAL(chanceChosen()));
}
/*
 * Shows the dialog with the rolled amount
 */
void DiceDialog::showDialog(const QString firstDiceValue, const QString secondDiceValue, const QString thirdDiceValue)
{
    firstDiceResult->setText(firstDiceValue);
    secondDiceResult->setText(secondDiceValue);
    thirdDiceResult->setText(thirdDiceValue);
    busButton->hide();
    chanceButton->hide();
    closeButton->show();

    this->exec();
}

void DiceDialog::showBusTicket(int succes)
{
    QMessageBox *busTicket = new QMessageBox();
    busTicket->setDefaultButton(QMessageBox::Ok);
    if (succes)
    {
        busTicket->setText("Busticket added to your cards. You can use it later in the game.");
        hideBusButtons();
    }
    else
        busTicket->setText("No bustickets left.");
    busTicket->exec();

}

void DiceDialog::hideBusButtons()
{
    busButton->setEnabled(false);
    chanceButton->setEnabled(false);
    closeButton->setEnabled(true);
    this->close();
}

void DiceDialog::showBusDialog()
{

    busButton->show();
    chanceButton->show();
    busButton->setEnabled(true);
    chanceButton->setEnabled(true);
    closeButton->setEnabled(false);

    this->exec();
}



