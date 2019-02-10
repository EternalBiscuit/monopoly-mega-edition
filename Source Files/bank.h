#ifndef BANK_H
#define BANK_H
#include <QObject>
class BusCard;
class PropertyCard;
class Player;

class Bank: public QObject
{
    Q_OBJECT
public:
    Bank();
    void giveMoney(Player& player);  // give an amount of money to the player
    void removeProperty(QString nameProperty);  // removes a property with a given name
    void addProperty(PropertyCard &card);   // adds a propertycard
    PropertyCard *getCard(QString cardName);    // searches for a propertycard with a name
    bool foundColourInBank(QColor colour);  // searches if a colour is in bank
    int getNumberOfColourCards(QColor colour);
    QList<PropertyCard*> getCards();
void read(const QJsonObject &json);
    void write(QJsonObject &json) const;

private:
    QList<BusCard*> usedBusCards;
    QList<PropertyCard*> propertyCards;

    void readStreetCardsFromFile(); // reads street cards from a file
    void readCompanyCardsFromFile();    // reads company cards from a file
    void readRailCardsFromFile();   // reads Rail Road cards from a file
    QColor getColorFromString(QString color);   // converts a QString colour to a QColor
	void instantiateWhichCard(const QJsonObject &json);
};

#endif // BANK_H
