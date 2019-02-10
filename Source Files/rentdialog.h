#ifndef RENTDIALOG_H
#define RENTDIALOG_H

#include <QDialog>

class QPushButton;
class QLabel;
class QGridLayout;

class RentDialog : public QDialog
{
    Q_OBJECT
public:
    RentDialog();
private:
    QPushButton* okButton;
    QLabel* rentPaid;
    QLabel* toOwner;
    QLabel* rentInfo;
    QLabel* toInfo;
    QGridLayout* layout;

public slots:
    void showDialog(int rent, int owner);

};

#endif // RENTDIALOG_H
