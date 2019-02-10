#include "jaildialog.h"

#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QMessageBox>

JailDialog::JailDialog()
{
    messageLabel = new QLabel("You're in jail, what do you want to do?", this);
    payButton = new QPushButton("Pay 50£", this);
    rollButton = new QPushButton("Roll", this);
    jailCardButton = new QPushButton("Use jailcard", this);
    message = new QMessageBox(this);

    layout = new QGridLayout(this);

    layout->addWidget(messageLabel, 0, 0);
    layout->addWidget(payButton, 1, 0);
    layout->addWidget(rollButton, 1, 1);
    layout->addWidget(jailCardButton, 1, 2);

    connect(payButton, SIGNAL(clicked(bool)), this, SIGNAL(payButtonClicked()));
    connect(rollButton, SIGNAL(clicked(bool)), this, SIGNAL(rollButtonClicked()));
    connect(jailCardButton, SIGNAL(clicked(bool)), this, SIGNAL(jailCardButtonClicked()));
    connect(message, SIGNAL(finished(int)), this, SLOT(close()));
}

void JailDialog::showjailCardMessage()
{
    message->setDefaultButton(QMessageBox::Ok);
    message->setWindowTitle("Used jailcard in jail");
    message->setText("You used a card to get out of jail. You may roll the dice to move.");
    message->exec();
}

void JailDialog::showPayMessage()
{
    message->setDefaultButton(QMessageBox::Ok);
    message->setWindowTitle("Paid in jail");
    message->setText("You paid to get out of jail. You may roll the dice.");
    message->exec();
}

void JailDialog::showRollMessage(bool succes, int firstDice, int secondDice)
{
    message->setDefaultButton(QMessageBox::Ok);
    message->setWindowTitle("Rolled in jail");

    if (succes)
    {
        message->setText("You rolled " + QString::number(firstDice) + " and " + QString::number(secondDice) + ".\nYou're free now.");
    }
    else
    {
        message->setText("You rolled " + QString::number(firstDice) + " and " + QString::number(secondDice) + ".\nIf you rolled three times, you have to pay.\nOtherwise you'll have to wait till next turn.");
    }

    message->exec();

}

void JailDialog::showDialog(bool hasJailCard)
{
    if (hasJailCard)
    {
        jailCardButton->setEnabled(true);
    }
    else
    {
        jailCardButton->setEnabled(false);
    }

    this->exec();
}

