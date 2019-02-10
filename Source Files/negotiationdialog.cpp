#include "negotiationdialog.h"
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QCheckBox>
#include <QIntValidator>
#include <QDebug>
#include <QMessageBox>

#include "propertycard.h"

NegotiationDialog::NegotiationDialog()
{
    setWindowTitle("Trade Properties");
    layout = new QGridLayout(this);

    acceptButton = new QPushButton("Accept", this);
    amountMoney = new QLineEdit(this);
    amountMoney->setValidator(new QIntValidator(0, 99999, this)); // only accept numbers

    QLabel* moneyLabel = new QLabel("Money", this);


    checkBoxLayout = new QVBoxLayout;

    transactionToPlayerLabel = new QLabel(this);
    propertyToTradeLabel = new QLabel(this);

    layout->addWidget(transactionToPlayerLabel, 0,0);
    layout->addWidget(propertyToTradeLabel,0,1);
    layout->addWidget(moneyLabel,1,0);
    layout->addWidget(amountMoney,1,1);
    layout->addLayout(checkBoxLayout,2,0);
    layout->addWidget(acceptButton,3,0);
    setLayout(layout);

    connect(acceptButton, &QPushButton::clicked, this, &NegotiationDialog::acceptClicked);
}

/*
 * Removes the old check boxes from the layout
 */
void NegotiationDialog::removeAllCheckBoxes()
{
    while(checkBoxLayout->count() != 0)
    {
        QWidget* widget = checkBoxLayout->itemAt(0)->widget();
        widget->hide();
        checkBoxLayout->removeWidget(widget);
        delete widget;
    }
}

/*
 * Asks for confirmation of the trade
 * returns true for accept and false for cancel
 */
bool NegotiationDialog::askConfirmation()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Accept/Decline");
    msgBox.setText("Does Player " + QString::number(askedPlayer +1) + " wish to accept the trade?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    int ret = msgBox.exec();
    switch(ret)
    {
    case QMessageBox::Yes:
    {
          return true;
          break;
    }
    case QMessageBox::No:
    {
          return false;
          break;
    }
    default:
    {
        return false;
        break;
    }
    }
}

/*
 * If accept is clicked, emit signal to model
 */
void NegotiationDialog::acceptClicked()
{
    if (askConfirmation())
    {
        for(int i = 0; i < checkBoxLayout->count(); i++)
        {
            QWidget* widget = checkBoxLayout->itemAt(i)->widget();
            QCheckBox* checkbox = qobject_cast<QCheckBox*> (widget);
            if (checkbox->isChecked())  // if checkbox is checked
                checkedProperties.append(checkbox->text());
        }
        // ask for confirmation

        emit trade(askingPlayer, checkedProperties, askedPlayer, propertyToTradeLabel->text(), amountMoney->text().toInt());
        close();
    }
}

/*
 * Shows the dialog for negotiation
 */
void NegotiationDialog::showNegotiation(int nAskingPlayer, QList<PropertyCard *> cards, int nAskedPlayer, QString propertyName)
{
    askingPlayer = nAskingPlayer;
    askedPlayer = nAskedPlayer;
    amountMoney->setText(0);
    removeAllCheckBoxes();
    checkedProperties.clear();

    transactionToPlayerLabel->setText("From Player " + QString::number(askingPlayer+1) + " to Player " + QString::number(askedPlayer+1) + " for ");
    propertyToTradeLabel->setText(propertyName);

    foreach(PropertyCard* card, cards)
    {
        QCheckBox* nameButton = new QCheckBox(card->getName(),this);
        checkBoxLayout->addWidget(nameButton);
    }
    exec();
}
