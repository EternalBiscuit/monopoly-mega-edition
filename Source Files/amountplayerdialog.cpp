#include "amountplayerdialog.h"
#include <QLabel>
#include <QComboBox>
#include <QGridLayout>
#include <QPushButton>

AmountPlayerDialog::AmountPlayerDialog()
{
    comboLabel = new QLabel(tr("Select the amount of players you want to play with:"), this);
    comboBox = new QComboBox(this);

    okButton = new QPushButton(this);
    okButton->setText("OK");

    for (int i = 2; i <= MAXPLAYERS; i++)
    {
        comboBox->addItem(QString::number(i));
    }

    layout = new QGridLayout(this);
    layout->addWidget(comboLabel, 0, 0);
    layout->addWidget(comboBox, 1, 0);
    layout->addWidget(okButton, 2, 2);

    connect(okButton, SIGNAL(clicked(bool)), this, SLOT(getSelectedValue()));

}

/*
 * Lets the user choose how many players are
 */
void AmountPlayerDialog::getSelectedValue()
{
    int currentIndex = (comboBox->currentIndex()) + 2;

    emit selected(currentIndex);
}
