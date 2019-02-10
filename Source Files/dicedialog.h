// Author: Sebastiaan
#ifndef DICEDIALOG_H
#define DICEDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QWidget>
#include <QPushButton>
#include <QGridLayout>

class DiceDialog : public QDialog
{
    Q_OBJECT
public:
    DiceDialog(QWidget* parent = 0);
public slots:
    void showDialog(const QString firstDiceValue, const QString secondDiceValue, const QString thirdDiceValue);
    void showBusTicket(int succes);
    void showBusDialog();
private slots:
    void hideBusButtons();
signals:
    void busTicketChosen();
    void chanceChosen();
private:
    QLabel* firstDiceResult;
    QLabel* secondDiceResult;
    QLabel* thirdDiceResult;
    QPushButton* closeButton;
    QPushButton* busButton;
    QPushButton* chanceButton;
    QGridLayout* layout;
};

#endif // DICEDIALOG_H
