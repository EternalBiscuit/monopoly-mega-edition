// Author: Ho Yuet
#include "buydialog.h"
#include <QGraphicsSimpleTextItem>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QDebug>

/*
 * Constructor of BuyDialog
 */
BuyDialog::BuyDialog()
{
    this->setWindowTitle("Buy property");
    nameLabel = new QLabel(tr("Property Name: "));
    nameText = new QLabel;
    priceLabel = new QLabel("Price: ");
    priceText= new QLabel;
    rentLabel = new QLabel("Rent: ");
    rentText = new QLabel;
    priceMortgageLabel = new QLabel("Mortgage price: ");
    priceMortgageText = new QLabel;
    buildingPriceLabel = new QLabel("Price per building: ");
    buildingPriceText = new QLabel;
    oneHouseLabel = new QLabel("1 house: ");
    oneHouseRentText = new QLabel;
    twoHouseLabel = new QLabel("2 houses: ");
    twoHouseRentText = new QLabel;
    threeHouseLabel = new QLabel(tr("3 houses: "));
    threeHouseRentText = new QLabel;
    fourHouseLabel = new QLabel(tr("4 houses: "));
    fourHouseRentText = new QLabel;
    hotelLabel = new QLabel(tr("Hotel: "));
    hotelRentText = new QLabel;
    skyLabel = new QLabel(tr("Skyscraper: "));
    skyRentText = new QLabel;

    buyButton = new QPushButton(this);
    buyButton->setText("Buy");
    auctionButton = new QPushButton(this);
    auctionButton->setText("Auction");

    layout = new QGridLayout;

    connect(buyButton, &QPushButton::clicked, this, &BuyDialog::buyButtonClicked);
    connect(buyButton, &QPushButton::clicked, this, &QDialog::close);
    connect(auctionButton, &QPushButton::clicked, this, &BuyDialog::passSpaceIndex);

}

/*
 * Shows a dialog with the given arguments (info for street)
 */
void BuyDialog::showDialog(QString streetName, int price, int rent, int priceMortgage, int buildingPrice, int oneHouseRent, int twoHouseRent, int threeHouseRent, int fourHouseRent, int hotelRent, int skyRent, bool auction, int spaceIndex)
{
    setStreetLayout();

    nameText->setText(streetName);
    priceText->setText(QString::number(price));
    rentText->setText(QString::number(rent));
    priceMortgageText->setText(QString::number(priceMortgage));
    buildingPriceText->setText(QString::number(buildingPrice));
    oneHouseRentText->setText(QString::number(oneHouseRent));
    twoHouseRentText->setText(QString::number(twoHouseRent));
    threeHouseRentText->setText(QString::number(threeHouseRent));
    fourHouseRentText->setText(QString::number(fourHouseRent));
    hotelRentText->setText(QString::number(hotelRent));
    skyRentText->setText(QString::number(skyRent));
    buildingPriceText->show();
    buildingPriceLabel->show();
    oneHouseRentText->show();
    oneHouseLabel->show();
    twoHouseRentText->show();
    twoHouseLabel->show();
    threeHouseRentText->show();
    threeHouseLabel->show();
    fourHouseRentText->show();
    fourHouseLabel->show();
    hotelRentText->show();
    hotelLabel->show();
    skyRentText->show();
    skyLabel->show();

    spaceInd = spaceIndex;

    if (auction)
    {
        auctionButton->hide();
        buyButton->hide();
        this->open();
        auctionButton->click();
    }
    else
    {
        auctionButton->show();
        buyButton->show();
        this->exec();
    }

}

void BuyDialog::showDialog(QString companyName, int price, int priceMortgage, bool auction, int spaceIndex)
{
    setCompanyLayout();

    nameText->setText(companyName);
    priceText->setText(QString::number(price));
    rentText->setText("1 utility: pips times 4\n2 utilities: pips times 10\n3 utilities: pips times 20");
    priceMortgageText->setText(QString::number(priceMortgage));
    buildingPriceText->hide();
    buildingPriceLabel->hide();
    oneHouseRentText->hide();
    oneHouseLabel->hide();
    twoHouseRentText->hide();
    twoHouseLabel->hide();
    threeHouseRentText->hide();
    threeHouseLabel->hide();
    fourHouseRentText->hide();
    fourHouseLabel->hide();
    hotelRentText->hide();
    hotelLabel->hide();
    skyRentText->hide();
    skyLabel->hide();

    spaceInd = spaceIndex;

    if (auction)
    {
        auctionButton->hide();
        buyButton->hide();
        this->open();
        auctionButton->click();
    }
    else
    {
        auctionButton->show();
        buyButton->show();
        this->exec();
    }

}

void BuyDialog::showDialog(QString stationName, int price, int priceMortgage, int priceDepot, bool auction, int spaceIndex)
{
    setStationLayout();

    nameText->setText(stationName);
    priceText->setText(QString::number(price));
    rentText->setText("25 times two for each station you have\nrent doubles with traindepot");
    priceMortgageText->setText(QString::number(priceMortgage));
    buildingPriceText->setText(QString::number(priceDepot));
    buildingPriceText->show();
    buildingPriceLabel->show();
    oneHouseRentText->hide();
    oneHouseLabel->hide();
    twoHouseRentText->hide();
    twoHouseLabel->hide();
    threeHouseRentText->hide();
    threeHouseLabel->hide();
    fourHouseRentText->hide();
    fourHouseLabel->hide();
    hotelRentText->hide();
    hotelLabel->hide();
    skyRentText->hide();
    skyLabel->hide();

    spaceInd = spaceIndex;

    if (auction)
    {
        auctionButton->hide();
        buyButton->hide();
        this->open();
        auctionButton->click();
    }
    else
    {
        auctionButton->show();
        buyButton->show();
        this->exec();
    }

}

void BuyDialog::passSpaceIndex()
{
    emit auctionButtonClicked(spaceInd);
}

void BuyDialog::setStreetLayout()
{
    delete layout;

    layout = new QGridLayout;

    layout->addWidget(nameLabel,0,0);
    layout->addWidget(nameText,0,1);
    layout->addWidget(priceLabel, 1,0);
    layout->addWidget(priceText,1,1);
    layout->addWidget(rentLabel,2,0);
    layout->addWidget(rentText,2,1);
    layout->addWidget(priceMortgageLabel,3,0);
    layout->addWidget(priceMortgageText,3,1);
    layout->addWidget(buildingPriceLabel,4,0);
    layout->addWidget(buildingPriceText,4,1);
    layout->addWidget(oneHouseLabel,5,0);
    layout->addWidget(oneHouseRentText,5,1);
    layout->addWidget(twoHouseLabel,6,0);
    layout->addWidget(twoHouseRentText,6,1);
    layout->addWidget(threeHouseLabel,7,0);
    layout->addWidget(threeHouseRentText,7,1);
    layout->addWidget(fourHouseLabel,8,0);
    layout->addWidget(fourHouseRentText,8,1);
    layout->addWidget(hotelLabel,9,0);
    layout->addWidget(hotelRentText,9,1);
    layout->addWidget(skyLabel,10,0);
    layout->addWidget(skyRentText,10,1);
    layout->addWidget(buyButton,11,0);
    layout->addWidget(auctionButton,11,1);

    setLayout(layout);
}

void BuyDialog::setCompanyLayout()
{
    delete layout;

    layout = new QGridLayout;

    layout->addWidget(nameLabel, 0, 0);
    layout->addWidget(nameText, 0, 1);
    layout->addWidget(priceLabel, 1, 0);
    layout->addWidget(priceText, 1, 1);
    layout->addWidget(rentLabel, 2, 0);
    layout->addWidget(rentText, 2, 1);
    layout->addWidget(priceMortgageLabel, 3, 0);
    layout->addWidget(priceMortgageText, 3, 1);
    layout->addWidget(buyButton,4,0);
    layout->addWidget(auctionButton,4,1);

    setLayout(layout);
}


void BuyDialog::setStationLayout()
{
    delete layout;

    layout = new QGridLayout;

    layout->addWidget(nameLabel, 0, 0);
    layout->addWidget(nameText, 0, 1);
    layout->addWidget(priceLabel, 1, 0);
    layout->addWidget(priceText, 1, 1);
    layout->addWidget(rentLabel, 2, 0);
    layout->addWidget(rentText, 2, 1);
    layout->addWidget(priceMortgageLabel, 3, 0);
    layout->addWidget(priceMortgageText, 3, 1);
    layout->addWidget(buildingPriceLabel, 4, 0);
    layout->addWidget(buildingPriceText, 4, 1);
    layout->addWidget(buyButton,5,0);
    layout->addWidget(auctionButton,5,1);

    setLayout(layout);
}



