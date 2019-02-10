//Author: Ho Yuet Cheung
#ifndef TRANSACTIONDIALOG_H
#define TRANSACTIONDIALOG_H
#include <QDialog>
class QLabel;
class QGridLayout;

class TransactionDialog: public QDialog
{
    Q_OBJECT
public:
    TransactionDialog();
    void setPropertiesText(QString name);
    void enableDisableButtons(int currentTurnPlayer, int clickedPlayerNumber);
private:
    QPushButton* tradeButton;
    QPushButton* mortgageButton;
    QLabel* nameProperty;
    QGridLayout* layout;
    int clickedPlayer;
    int currentPlayer;
signals:
    void trade(int askingPlayer, int askedPlayer, QString name);
    void mortgage(QString name);
private slots:
    void tradeClicked();
    void mortgageClicked();
};

#endif // TRANSACTIONDIALOG_H
