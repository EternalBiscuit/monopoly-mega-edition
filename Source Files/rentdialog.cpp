#include "rentdialog.h"
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>

RentDialog::RentDialog()
{
    okButton = new QPushButton("OK", this);

    rentPaid = new QLabel("Rent paid: ", this);
    rentInfo = new QLabel(this);

    toOwner = new QLabel("To: Player ", this);
    toInfo = new QLabel(this);

    layout = new QGridLayout(this);
    layout->addWidget(rentPaid, 0, 0);
    layout->addWidget(rentInfo, 0, 1);
    layout->addWidget(toOwner, 1, 0);
    layout->addWidget(toInfo, 1, 1);
    layout->addWidget(okButton, 2, 3);

    connect(okButton, SIGNAL(clicked(bool)), this, SLOT(close()));
}

void RentDialog::showDialog(int rent, int owner)
{
    rentInfo->setText(QString::number(rent));
    toInfo->setText((QString::number(owner + 1)));

    this->exec();
}



