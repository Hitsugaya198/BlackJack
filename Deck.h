#ifndef DECK_H
#define DECK_H

#include "Suit.h"
#include <QVector>

class Deck
{
  public:
    Deck();
    ~Deck();

    QSet<Suit*> getSuits() const;
    void shuffleDeck();
    Card* pullCard();

    int getCardCount() const;

  private:

    QSet<Suit*> suits_;
    void initialiseDeck();


    // Deck order implies a unique value per Card per Suit
    QVector<QPair<suits,Card*>> deckOrder_;

    int cardCount_;
    void cleanOutDeck();
};

#endif // DECK_H
