#ifndef PROPERTIESDIALOG_H
#define PROPERTIESDIALOG_H
#include <QDialog>

class QLabel;
class PropertyCard;
class QVBoxLayout;
class QPushButton;
class TransactionDialog;

class PropertiesDialog: public QDialog
{
    Q_OBJECT
public:
    PropertiesDialog();
    void getProperties(QList<PropertyCard*> playerProperties, int currentTurnPlayer, int clickedPlayerNumber);
    TransactionDialog* getTransactionDialog();
private:
    QVBoxLayout* propertiesArea;
    QList<QPushButton*> properties;
    TransactionDialog* transactionDialog;
    int clickedPlayer;
    int currentPlayer;
    void removeAllProperties();
private slots:
    void pushedProperty();

};

#endif // PROPERTIESDIALOG_H
