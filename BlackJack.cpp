#include "BlackJack.h"

BlackJack::BlackJack():
  QObject()
{
  // BlackJack needs a deck of cards.
  deck_ = new Deck();

  connect(BlackJackStateMachine::instance(), SIGNAL(stateChanged(gameStates)), this, SLOT(stateChangedSlot(gameStates)));
}

BlackJack::~BlackJack()
{
  // Bye bye deck of cards.
  delete deck_;
}

QPair<Card *, Card *> BlackJack::deal(participants whoDunnit)
{
  // A BlackJack deal returns 2 cards.
  Card *c1, *c2;

  // So, we simply call hitMe, and tell who it is (dealer or player).
  c1 = hitMe(whoDunnit);
  if(c1 == nullptr)
    return QPair <Card *, Card *>{};

  // We call hitMe twice, because a deal needs two cards returned.
  c2 = hitMe(whoDunnit, true);
  if(c2 == nullptr)
    return QPair <Card *, Card *>{};

  // We create the pair to be passed to the GUI
  QPair <Card *, Card *> pair{c1,c2};

  return pair;
}

void BlackJack::updateState()
{
  BlackJackStateMachine::instance()->calcState(playerCards_, dealerCards_);
}

void BlackJack::updateState(bool callGame)
{
  BlackJackStateMachine::instance()->calcState(playerCards_, dealerCards_, callGame);
}

void BlackJack::addCard(participants whoDunnit, Card* card)
{
  if(whoDunnit == PLAYER)
  {
    playerCards_.insert(card);
  }
  else
  {
    dealerCards_.insert(card);
  }
}

void BlackJack::stateChangedSlot(gameStates state)
{
  emit stateChanged(state);
}

void BlackJack::addCards(participants whoDunnit, QPair <Card *, Card *> pair)
{
  addCard(whoDunnit, pair.first);
  addCard(whoDunnit, pair.second);
}

Card* BlackJack::hitMe(participants whoDunnit, bool triggerUpdate)
{
  // A hit in BlackJack only has one card.
  Card *c1;

  // So, we pull one from the deck.
  c1 = deck_->pullCard();
  if(c1 != nullptr)
  {
    addCard(whoDunnit, c1);
    // Depending on who gets the card, we increment counters accordingly.
    if(whoDunnit == PLAYER)
      ++playerCardCount_;
    else ++dealerCardCount_;

    // We update the game state.
    if(triggerUpdate)
      QTimer::singleShot(100, Qt::PreciseTimer, this, SLOT(updateState()));

    return c1;
  }
  return nullptr;
}

void BlackJack::shuffleDeck()
{
  for(int i = 0; i < 10; ++i)
  {
    deck_->shuffleDeck();
  }
  playerCardCount_ = 0;
  dealerCardCount_ = 0;
  playerCards_.clear();
  dealerCards_.clear();
}

int BlackJack::getCardCount() const
{
  return deck_->getCardCount();
}

int BlackJack::getPlayerCardCount() const
{
  return playerCardCount_;
}

int BlackJack::getDealerCardCount() const
{
  return dealerCardCount_;
}

int BlackJack::getPlayerCardsValue() const
{
  return BlackJackStateMachine::instance()->playerValue();
}

int BlackJack::getDealerCardsValue() const
{
  return BlackJackStateMachine::instance()->dealerValue();
}

QSet<Card *> BlackJack::getDealerCards() const
{
  return dealerCards_;
}
