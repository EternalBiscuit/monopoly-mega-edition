#ifndef JAILDIALOG_H
#define JAILDIALOG_H

#include <QDialog>

class QLabel;
class QPushButton;
class QGridLayout;
class QMessageBox;

class JailDialog : public QDialog
{
    Q_OBJECT
public:
    JailDialog();
private:
    QLabel* messageLabel;
    QPushButton* payButton;
    QPushButton* rollButton;
    QPushButton* jailCardButton;
    QGridLayout* layout;
    QMessageBox* message;
public slots:
    void showjailCardMessage();
    void showPayMessage();
    void showRollMessage(bool succes, int firstDice, int secondDice);
    void showDialog(bool hasJailCard);
signals:
    void payButtonClicked();
    void rollButtonClicked();
    void jailCardButtonClicked();

};

#endif // JAILDIALOG_H
