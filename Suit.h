#ifndef SUIT_H
#define SUIT_H

#include <QSet>
#include <QPair>

#include "Card.h"
#include "Suits.h"

class Suit
{
  public:
    Suit(suits suit);
    ~Suit();

//    typedef QPair<faces, int> cardType;
    typedef QSet<Card*> cardContainer;

    suits getSuit() { return suit_; }
    cardContainer &getCards() { return cards_; }


  private:
    suits suit_;
    cardContainer cards_;

    void initialiseSuit();
    void cleanOutCards();
};

#endif // SUIT_H
