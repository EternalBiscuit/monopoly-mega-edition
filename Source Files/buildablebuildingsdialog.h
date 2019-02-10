#ifndef BUILDABLEBUILDINGSDIALOG_H
#define BUILDABLEBUILDINGSDIALOG_H
#include <QDialog>
class QVBoxLayout;
class QLabel;
class QPushButton;
class BuildBuildingDialog;
#include "board.h"
#include "propertycard.h"

class BuildableBuildingsDialog: public QDialog
{
    Q_OBJECT
public:
    BuildableBuildingsDialog();
    void getProperties(QList<PropertyCard*>listProperties, Board::TypeTransaction newTransaction);
    BuildBuildingDialog* getBuildBuildingDialog();
private:
    QVBoxLayout* layout;
    QList<QPushButton*> colourProperties;
    QList<PropertyCard*> cards;
    BuildBuildingDialog* buildBuildingDialog;
    void removeAllProperties();
    int getCorrectPriceCard(QColor colour);
    Board::TypeTransaction transaction;
private slots:
    void pushedProperty();
signals:
    void getMaxAmountBuyableBuildings(QColor colour);
    void getMaxAmountSellableBuildings(QColor colour);
};

#endif // BUILDABLEBUILDINGSDIALOG_H

