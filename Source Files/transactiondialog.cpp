//Author: Ho Yuet Cheung
#include "transactiondialog.h"
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>

TransactionDialog::TransactionDialog()
{
    setWindowTitle("Transaction");
    nameProperty = new QLabel(this);

    setFixedSize(300,100);
    tradeButton = new QPushButton(this);
    tradeButton->setText("Trade");

    mortgageButton = new QPushButton(this);
    mortgageButton->setText("Mortgage");

    layout = new QGridLayout(this);
    layout->addWidget(nameProperty,0,0);
    layout->addWidget(tradeButton,1,0);
    layout->addWidget(mortgageButton,1,1);
    setLayout(layout);

    connect(tradeButton, &QPushButton::clicked, this, &TransactionDialog::tradeClicked);
    connect(mortgageButton, &QPushButton::clicked, this, &TransactionDialog::mortgageClicked);

}

void TransactionDialog::setPropertiesText(QString name)
{
    if (name.endsWith("(M)"))
    {
        mortgageButton->setText("Lift mortgage");
        name.remove(name.count()-4, name.count());// remove the indicator of mortgaged property
    }
    else
        mortgageButton->setText("Mortgage");
    nameProperty->setText(name);
}

/*
 * Enables or disables buttons depending who activated this dialog
 */
void TransactionDialog::enableDisableButtons(int currentTurnPlayer, int clickedPlayerNumber)
{
    currentPlayer = currentTurnPlayer;
    clickedPlayer = clickedPlayerNumber;
    if (currentPlayer == clickedPlayer)
    {
        tradeButton->setEnabled(false);
        mortgageButton->setEnabled(true);
    }
    else
    {
        tradeButton->setEnabled(true);
        mortgageButton->setEnabled(false);
    }
}

void TransactionDialog::tradeClicked()
{
    close();
    emit trade(currentPlayer, clickedPlayer, nameProperty->text());
}

void TransactionDialog::mortgageClicked()
{
    close();
    emit mortgage(nameProperty->text());
}


