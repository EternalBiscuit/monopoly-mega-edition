#ifndef NEGOTIATIONDIALOG_H
#define NEGOTIATIONDIALOG_H
#include <QDialog>
class QVBoxLayout;
class QGridLayout;
class QLineEdit;
class PropertyCard;
class QLabel;

class NegotiationDialog: public QDialog
{
    Q_OBJECT
public:
    NegotiationDialog();
private:
    QVBoxLayout* checkBoxLayout;
    QPushButton* acceptButton;
    QGridLayout* layout;
    QLineEdit* amountMoney;
    QLabel* transactionToPlayerLabel;
    QLabel* propertyToTradeLabel;
    QList<QString> checkedProperties;
    int askingPlayer;
    int askedPlayer;
    void removeAllCheckBoxes();
    bool askConfirmation();
private slots:
    void acceptClicked();
public slots:
    void showNegotiation(int nAskingPlayer, QList<PropertyCard*> cards, int nAskedPlayer, QString propertyName);
signals:
    void trade(int askingPlayer, QList<QString> toGiveProperties, int toPlayer, QString askedPropertyName, int amountMoney);
};

#endif // NEGOTIATIONDIALOG_H
