//Author: Ho Yuet Cheung
#include "propertiesdialog.h"
#include "propertycard.h"
#include "transactiondialog.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QDebug>

PropertiesDialog::PropertiesDialog()
{
    propertiesArea = new QVBoxLayout(this);

    this->setWindowTitle("Properties");
    this->setMinimumSize(280,100);
    propertiesArea->setSizeConstraint(QLayout::SetMaximumSize);

    transactionDialog = new TransactionDialog;
    connect(transactionDialog, &TransactionDialog::finished, this, &PropertiesDialog::close);
}

/*
 * Shows the properties in a dialog
 */
void PropertiesDialog::getProperties(QList<PropertyCard *> playerProperties, int currentTurnPlayer, int clickedPlayerNumber)
{
    clickedPlayer = clickedPlayerNumber;
    currentPlayer = currentTurnPlayer;

    setWindowTitle("Player" + QString::number(clickedPlayer+1) + " properties");
    removeAllProperties();
    int iterator = 0;

    foreach(PropertyCard* card, playerProperties)
    {
        QString name = card->getName();

        if (card->checkIfMortgaged())
            properties.append(new QPushButton(name + " (M)"));  // show mortgaged property
        if (!card->checkIfMortgaged())
            properties.append(new QPushButton(name));
        properties[iterator]->setFlat(true);

        connect(properties[iterator], &QPushButton::clicked, this, &PropertiesDialog::pushedProperty);
        propertiesArea->addWidget(properties[iterator++]);
    }
    exec();
}

/*
 * getter for connection in BoardView
 */
TransactionDialog *PropertiesDialog::getTransactionDialog()
{
    return transactionDialog;
}

/*
 * Removes all old properties
 */
void PropertiesDialog::removeAllProperties()
{
    if (!properties.isEmpty())
    {
        properties.clear(); // clear the old list of properties
    }


    // delete all old labels
    while(propertiesArea->count() != 0)
    {
        QWidget *widget = propertiesArea->itemAt(0)->widget();
        widget->hide();
        widget->disconnect();   // remove the old connection
        propertiesArea->removeWidget(widget);
        delete widget;
    }
}



/*
 * Opens a dialog to sell or mortgage if you push on a property
 */
void PropertiesDialog::pushedProperty()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());   // get the clicked button
    QString name = buttonSender->text();

    transactionDialog->setPropertiesText(name);
    transactionDialog->enableDisableButtons(currentPlayer,clickedPlayer);
    transactionDialog->exec();
}
