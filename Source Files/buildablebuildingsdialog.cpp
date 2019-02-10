// Author: Ho Yuet
#include "buildablebuildingsdialog.h"
#include "buildbuildingdialog.h"
#include "propertycard.h"
#include "streetcard.h"
#include "railroadcard.h"
#include <QDebug>
#include <QList>
#include <QGraphicsRectItem>
#include <QVBoxLayout>
#include <QPushButton>

BuildableBuildingsDialog::BuildableBuildingsDialog()
{
    buildBuildingDialog = new BuildBuildingDialog;

    layout = new QVBoxLayout(this);
    setWindowTitle("Buildable places");
    setMinimumSize(270,100);


}

void BuildableBuildingsDialog::getProperties(QList<PropertyCard *> listProperties, Board::TypeTransaction newTransaction)
{
    transaction = newTransaction;
    if (transaction == Board::TypeTransaction::SELL)
        setWindowTitle("Removable places");
    else
        setWindowTitle("Buildable places");

    removeAllProperties();
    int iterator = 0;

    foreach(PropertyCard* card, listProperties)
    {
        cards.append(listProperties[iterator]);
        colourProperties.append(new QPushButton);
        QPalette pal = colourProperties[iterator]->palette();
        pal.setColor(QPalette::Button, card->getColour());
        colourProperties[iterator]->setAutoFillBackground(true);
        colourProperties[iterator]->setPalette(pal);
        colourProperties[iterator]->setFlat(true);
        colourProperties[iterator]->update();

        connect(colourProperties[iterator], &QPushButton::clicked, this, &BuildableBuildingsDialog::pushedProperty);
        layout->addWidget(colourProperties[iterator++]);
    }
    exec();

}

/*
 * Returns the dialog for connection
 */
BuildBuildingDialog *BuildableBuildingsDialog::getBuildBuildingDialog()
{
    return buildBuildingDialog;
}

void BuildableBuildingsDialog::removeAllProperties()
{
    if (!colourProperties.isEmpty())
    {
        colourProperties.clear(); // clear the old list of properties
        cards.clear();
    }
    while(layout->count() != 0)
    {
        QWidget *widget = layout->itemAt(0)->widget();
        widget->hide();
        widget->disconnect();   // remove the old connection
        layout->removeWidget(widget);
        delete widget;
    }
}

/*
 * Gets the correct price from the given colour
 */
int BuildableBuildingsDialog::getCorrectPriceCard(QColor colour)
{
    foreach(PropertyCard* card, cards)
    {
        if (card->getColour() == colour)    //search for the correct colour and return the price
        {
            return card->getBuildingPrice();
        }
    }
    return 0;
}

/*
 * Opens a dialog if you push on a property
 */
void BuildableBuildingsDialog::pushedProperty()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());   // get the clicked button
    QColor colour = (((buttonSender->palette()).button()).color());
    int price = getCorrectPriceCard(colour);

    buildBuildingDialog->setColourPrice(colour, price, transaction);
    if (transaction == Board::TypeTransaction::BUY)
        emit getMaxAmountBuyableBuildings(colour);
    else if (transaction == Board::TypeTransaction::SELL)
        emit getMaxAmountSellableBuildings(colour);
}

