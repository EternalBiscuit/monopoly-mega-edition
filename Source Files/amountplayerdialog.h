#ifndef AMOUNTPLAYERDIALOG_H
#define AMOUNTPLAYERDIALOG_H

#include <QDialog>

class QComboBox;
class QLabel;
class QGridLayout;
class QPushButton;

class AmountPlayerDialog : public QDialog
{
    Q_OBJECT
public:
    AmountPlayerDialog();
private:
    static const int MAXPLAYERS = 8;
    QComboBox* comboBox;
    QLabel* comboLabel;
    QGridLayout* layout;
    QPushButton* okButton;
private slots:
    void getSelectedValue();
signals:
    void selected(int numberPlayers);
};

#endif // AMOUNTPLAYERDIALOG_H
