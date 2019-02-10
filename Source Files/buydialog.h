// Author: Ho Yuet
#ifndef BUYDIALOG_H
#define BUYDIALOG_H
#include <QDialog>

class QGraphicsSimpleTextItem;
class QGridLayout;
class QLabel;

class BuyDialog: public QDialog
{
    Q_OBJECT
public:
    BuyDialog();
private:
    QLabel* nameText;
    QLabel* nameLabel;
    QLabel* priceText;
    QLabel* priceLabel;
    QLabel* rentText;
    QLabel* rentLabel;
    QLabel* priceMortgageText;
    QLabel* priceMortgageLabel;
    QLabel* buildingPriceText;
    QLabel* buildingPriceLabel;
    QLabel* oneHouseRentText;
    QLabel* oneHouseLabel;
    QLabel* twoHouseRentText;
    QLabel* twoHouseLabel;
    QLabel* threeHouseRentText;
    QLabel* threeHouseLabel;
    QLabel* fourHouseRentText;
    QLabel* fourHouseLabel;
    QLabel* hotelRentText;
    QLabel* hotelLabel;
    QLabel* skyRentText;
    QLabel* skyLabel;
    QPushButton* buyButton;
    QPushButton* auctionButton;
    QGridLayout* layout;

    int spaceInd;

    void setStreetLayout();
    void setStationLayout();
    void setCompanyLayout();
signals:
    void buyButtonClicked();    // on click of the buy button
    void auctionButtonClicked(int spaceIndex); // on click of the auction button
public slots:
    void showDialog(QString streetName, int price, int rent, int priceMortgage, int buildingPrice, int oneHouseRent, int twoHouseRent,
                    int threeHouseRent, int fourHouseRent, int hotelRent, int skyRent, bool auction, int spaceIndex);
    void showDialog(QString companyName, int price, int priceMortgage, bool auction, int spaceIndex);
    void showDialog(QString stationName, int price, int priceMortgage, int priceRailRoad, bool auction, int spaceIndex);
private slots:
    void passSpaceIndex();
};

#endif // BUYDIALOG_H
