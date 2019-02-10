//Author: Ho Yuet
#ifndef BUILDBUILDINGDIALOG_H
#define BUILDBUILDINGDIALOG_H
#include <QDialog>
#include "board.h"
class QGridLayout;
class QComboBox;
class QLabel;
class QPushButton;

class BuildBuildingDialog: public QDialog
{
    Q_OBJECT
public:
    BuildBuildingDialog();
    void setColourPrice(QColor newColour, int newPrice, Board::TypeTransaction newTransaction);
private:
    Board::TypeTransaction transaction;
    QGridLayout* layout;
    QComboBox* amountBuildingBox;
    QLabel* priceBuildingLabel;
    QPushButton* confirmButton;
    QColor streetColour;
    QLabel* askLabel;
    int price;
private slots:
    void pressedOk();
public slots:
    void showBuildableBuildings(int maxAmount);
    void showSellableBuildings(int maxAmount);
signals:
    void buildBuildings(QColor colour, int amount);
    void sellBuildings(QColor colour, int amount);
};

#endif // BUILDBUILDINGDIALOG_H

