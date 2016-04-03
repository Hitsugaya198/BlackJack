/*
 * BlackJack.cpp
 *
 * Author  : Louis Parkin
 * Purpose : Provides an API to the GUI for
 *           interacting with the deck of cards
 */

#include "Deck.h"
#include <QDebug>
#include <ctime>

Deck::Deck()
{
  initialiseDeck();
  qDebug() << "Deck Initialised";
}

Deck::~Deck()
{
  cleanOutDeck();
  qDebug() << "Deck Destroyed";
}

QSet<Suit*> Deck::getSuits() const
{
  return suits_;
}

void Deck::cleanOutDeck()
{
  QSet<Suit*>::iterator i = suits_.begin();

  while(i != suits_.end())
  {
    Suit* suit = *i;
    ++i;
    delete suit;
  }

  suits_.clear();
  qDebug() << "Deck Cleared";
}

void Deck::initialiseDeck()
{
  cleanOutDeck();

  for(int x = CLUBS; x < max_suits; ++x)
  {
    Suit *suit = new Suit{static_cast<suits>(x)};
    suits_.insert(suit);
  }

  if(!deckOrder_.isEmpty()) deckOrder_.clear();

  QSet<Suit*>::iterator i = suits_.begin();
  while(i != suits_.end())
  {
    Suit* currentSuit = *i; ++i;
    Suit::cardContainer& cards = currentSuit->getCards();
    Suit::cardContainer::iterator j = cards.begin();

    while(j != cards.end())
    {
      Card* card = *j; ++j;
      QPair<suits,Card*> pair{currentSuit->getSuit(), card};
      deckOrder_.append(pair);
    }
  }
  cardCount_ = deckOrder_.count();
}
int Deck::getCardCount() const
{
  return cardCount_;
}


void Deck::shuffleDeck()
{
  if(deckOrder_.isEmpty())
  {
    qDebug() << "Can't shuffle an empty deck dufus!";
    return;
  }

  QVector<QPair<suits,Card*>>::iterator i = deckOrder_.begin();

  QVector<QPair<suits,Card*>> temp;
  std::srand(std::time(0)); // Seed the randomizer.

  while (!deckOrder_.isEmpty()) // Run through the current deck, in order.
  {
    int len = deckOrder_.size()-1;
    int idx = std::rand() / 100 % 10; // Pick a random index within the first 10 cards
    int frontOrBack = 0;

    if(len < idx) idx = len; // If the idx is bigger than the number of cards left, take from the back.
    if(len % 2 == 0) frontOrBack = len; // If the length is divisible by two, start from the back.
    else frontOrBack = idx * 2; // Else make sure that frontOrBack - idx == idx.

    temp.append(deckOrder_.takeAt(frontOrBack - idx)); // Take from deckOrder_ and add to temp.
  }

  deckOrder_ = QVector<QPair<suits,Card*>> {temp}; // Create a new deckOrder_ from temp.

  cardCount_ = deckOrder_.count(); // Update the deck counter.
}

Card *Deck::pullCard()
{
  // Physically remove a card from the deckOrder and send it back to the caller.
  if(!deckOrder_.isEmpty())
  {
    cardCount_--;
    return deckOrder_.takeAt(0).second; // Caller doesn't own this card, as it is still in the deck, just not in the ordered deck anymore.
  }
  else return nullptr;
}
