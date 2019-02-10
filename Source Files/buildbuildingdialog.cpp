//Author: Ho Yuet
#include "buildbuildingdialog.h"
#include <QComboBox>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>

BuildBuildingDialog::BuildBuildingDialog()
{
    setWindowTitle("Buy buildings");
    askLabel = new QLabel(this);
    askLabel->setText("Choose how many buildings you want to build.");
    priceBuildingLabel = new QLabel(this);
    QLabel* buildingLabel = new QLabel(this);
    buildingLabel->setText("Price per building");

    amountBuildingBox = new QComboBox(this);

    confirmButton = new QPushButton(this);
    confirmButton->setText("Ok");


    layout = new QGridLayout(this);
    layout->addWidget(askLabel, 0,0);
    layout->addWidget(buildingLabel,1,0);
    layout->addWidget(priceBuildingLabel,2,0);
    layout->addWidget(amountBuildingBox,3,0);
    layout->addWidget(confirmButton,3,1);
    setLayout(layout);
    connect(confirmButton, &QPushButton::clicked, this, &BuildBuildingDialog::pressedOk);
}

void BuildBuildingDialog::showBuildableBuildings(int maxAmount)
{
    setWindowTitle("Buy buildings");
    askLabel->setText("Choose how many buildings you want to build.");
    amountBuildingBox->clear();
    priceBuildingLabel->setText(QString::number(price));
    for(int i = 0; i <= maxAmount; i++)
    {
        amountBuildingBox->addItem(QString::number(i));
    }
    exec();
}

/*
 * Shows sellable amount of buildings
 */
void BuildBuildingDialog::showSellableBuildings(int maxAmount)
{
    setWindowTitle("Sell buildings");
    askLabel->setText("Choose how many buildings you wish to sell.");
    amountBuildingBox->clear();
    priceBuildingLabel->setText(QString::number(price));
    for(int i = 0; i <= maxAmount; i++)
    {
        amountBuildingBox->addItem(QString::number(i));
    }
    exec();
}

void BuildBuildingDialog::setColourPrice(QColor newColour, int newPrice, Board::TypeTransaction newTransaction)
{
    transaction = newTransaction;
    streetColour = newColour;
    price = newPrice;
}

/*
 * Emits a signal with how many building the player wants
 */
void BuildBuildingDialog::pressedOk()
{
    int amount = (amountBuildingBox->currentIndex());
    if (transaction == Board::TypeTransaction::BUY)
        emit buildBuildings(streetColour, amount);
    else if (transaction == Board::TypeTransaction::SELL)
        emit sellBuildings(streetColour, amount);
    close();
}



