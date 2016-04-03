#include "Suit.h"
#include <QDebug>

Suit::Suit(suits suit)
{
  // This Suit has to remember what it is.
  suit_ = suit;

  // Create all the cards.
  initialiseSuit();
  qDebug() << "Suit" << suit_ << "Initialised";
}

Suit::~Suit()
{
  // Kill all the cards.
  cleanOutCards();

  qDebug() << "Suit" << suit_ << "Destroyed";
}

void Suit::cleanOutCards()
{
  cardContainer::iterator i = cards_.begin();

  while(i != cards_.end()) // Run through the suit.
  {
    Card* card = *i;
    ++i;
    delete card; // Delete each individual card
  }

  cards_.clear();
  qDebug() << "Suit" << suit_ << "Cleared";
}

void Suit::initialiseSuit()
{
  QVector<faceValues>::iterator value = faceValuesVector.begin();
  // From ACE to KING
  for(int x = ACE; x < max_faces; ++x)
  {
    // Create a card with face x and facevalue value (++).
    Card* card = new Card{static_cast<faces>(x), *(value++), suit_};

    // Add card to the suit.
    cards_.insert(card);
  }
}

