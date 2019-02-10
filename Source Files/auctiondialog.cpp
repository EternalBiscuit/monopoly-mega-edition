#include "auctiondialog.h"
#include <QLabel>
#include <QGridLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QMessageBox>

AuctionDialog::AuctionDialog(int players)
{
    layout = new QGridLayout(this);
    bidButton = new QPushButton(this);
    forfaitButton = new QPushButton(this);
    amountText = new QTextEdit(this);
    currentPlayerLabel = new QLabel(this);
    highestBidLabel = new QLabel(this);
    highestPlayerLabel = new QLabel(this);
    highestInfoLabel = new QLabel(this);

    createPlayerLabels(players);

    currentPlayer = 0;

    amountText->setMaximumSize(bidButton->sizeHint());

    bidButton->setText("Set bid");
    forfaitButton->setText("Forfait");
    highestInfoLabel->setText("Highest bid: ");

    layout->addWidget(currentPlayerLabel, 2, 0);
    layout->addWidget(bidButton, 2, 1);
    layout->addWidget(amountText, 2, 2);
    layout->addWidget(forfaitButton, 3, 1);
    layout->addWidget(highestInfoLabel, 4, 0);
    layout->addWidget(highestPlayerLabel, 4, 1);
    layout->addWidget(highestBidLabel, 4, 2);

    connect(bidButton, SIGNAL(clicked(bool)), this, SLOT(getBidValue()));
    connect(forfaitButton, SIGNAL(clicked(bool)), this, SLOT(forfait()));
}

void AuctionDialog::switchTurn()
{
    int nextPlayer = (currentPlayer + 1) % playerLabels.count();
    while (playerLabels[nextPlayer]->isHidden() && currentPlayer != nextPlayer)
    {
        nextPlayer = (nextPlayer + 1) % playerLabels.count();
    }

    if (currentPlayer != nextPlayer)
    {
        currentPlayer = nextPlayer;
        currentPlayerLabel->setText("Player: " + QString::number(currentPlayer + 1));
    }
}

void AuctionDialog::closeDialog()
{
    QMessageBox* done = new QMessageBox(this);

    done->setText(highestPlayerLabel->text() + " won with a bid of " + highestBidLabel->text());
    done->setStandardButtons(QMessageBox::Ok);

    done->exec();

    this->close();
    emit auctionDone(currentPlayer, highestBidLabel->text().toInt(), spaceInd);
    emit closeBuyDialog();
}

void AuctionDialog::showDialog(int spaceIndex)
{
    reset();

    spaceInd = spaceIndex;

    this->exec();
}

void AuctionDialog::processBid(bool bidOK)
{
    if (bidOK)
    {
        highestBidLabel->setText(amountText->toPlainText());
        highestPlayerLabel->setText("Player: " + QString::number(currentPlayer + 1));
        bidLabels[currentPlayer]->setText(amountText->toPlainText());
        switchTurn();

        int prevAmount = amountText->toPlainText().toInt();
        amountText->setText(QString::number(prevAmount+1));
        amountText->selectAll();
    }
    else
    {
        QMessageBox* balanceTooLow = new QMessageBox(this);

        balanceTooLow->setText("You don't have enough money to do the bid. Either forfait or do a lower bid.");
        balanceTooLow->setStandardButtons(QMessageBox::Ok);

        balanceTooLow->exec();
    }
}

void AuctionDialog::getBidValue()
{
    QString amountStr = amountText->toPlainText();

    int amountNum = amountStr.toInt();

    if (amountNum == 0)
    {
        QMessageBox* wrongInput = new QMessageBox(this);

        wrongInput->setText("Wrong bid input, input has to be a number greater than zero.");
        wrongInput->setStandardButtons(QMessageBox::Ok);

        wrongInput->exec();
    }
    else
    {
        if (amountNum <= highestBidLabel->text().toInt())
        {
            QMessageBox* bidTooLow = new QMessageBox(this);

            bidTooLow->setText("Your bid is too low, either forfait or do a higher bid.");
            bidTooLow->setStandardButtons(QMessageBox::Ok);

            bidTooLow->exec();
        }
        else
        {
            emit requestBid(currentPlayer, amountNum);

        }
    }
}

void AuctionDialog::forfait()
{
    playerLabels[currentPlayer]->hide();
    bidLabels[currentPlayer]->hide();

    switchTurn();

    checkAuctionDone();
}

void AuctionDialog::checkAuctionDone()
{
    int i = 0;

    foreach (QLabel* label, playerLabels)
    {
        if (!(label->isHidden()))
        {
            i++;
        }
    }

    if (i <= 1)
    {
        closeDialog();
    }
}

void AuctionDialog::createPlayerLabels(int players)
{
    for (int i = 0; i < players; i++)
    {
        playerLabels.append(new QLabel("Player " + QString::number(i+1), this));
        bidLabels.append(new QLabel(this));
        layout->addWidget(playerLabels[i], 0, i);
        layout->addWidget(bidLabels[i], 1, i);
    }
}

void AuctionDialog::reset()
{
    foreach (QLabel* label, bidLabels)
    {
        label->setText("0");
        label->show();
    }
    foreach (QLabel* label, playerLabels)
    {
        label->show();
    }

    currentPlayer = 0;

    amountText->setText("0");
    amountText->selectAll();
    amountText->setFocus();

    currentPlayerLabel->setText("Player: " + QString::number(currentPlayer + 1));
    highestBidLabel->setText("0");
    highestPlayerLabel->setText("");
}
