#ifndef AUCTIONDIALOG_H
#define AUCTIONDIALOG_H

#include <QDialog>

class QLabel;
class QPushButton;
class QTextEdit;
class QGridLayout;


class AuctionDialog : public QDialog
{
    Q_OBJECT
public:
    AuctionDialog(int players);
private:
    QList<QLabel*> playerLabels;
    QList<QLabel*> bidLabels;
    QPushButton* bidButton;
    QPushButton* forfaitButton;
    QTextEdit* amountText;
    QGridLayout* layout;
    QLabel* currentPlayerLabel;
    QLabel* highestBidLabel;
    QLabel* highestPlayerLabel;
    QLabel* highestInfoLabel;
    int currentPlayer;
    int spaceInd;
    void closeDialog();
    void switchTurn();
    void checkAuctionDone();
    void createPlayerLabels(int players);
    void reset();
public slots:
    void showDialog(int spaceIndex);
    void processBid(bool bidOK);
private slots:
    void getBidValue();
    void forfait();
signals:
    void requestBid(int player, int amount);
    void auctionDone(int player, int amount,int spaceIndex);
    void closeBuyDialog();



};

#endif // AUCTIONDIALOG_H
