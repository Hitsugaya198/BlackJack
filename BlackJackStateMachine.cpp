#include "BlackJackStateMachine.h"
#include <QSet>

BlackJackStateMachine *BlackJackStateMachine::instance_ = 0;

BlackJackStateMachine::BlackJackStateMachine(QObject *parent):
  QObject(parent),
  state_(CONTINUE_NORMAL_PLAY)
{

}

BlackJackStateMachine::~BlackJackStateMachine()
{
  delete instance_;
}

gameStates BlackJackStateMachine::state() const
{
  return state_;
}

void BlackJackStateMachine::calcState(QSet<Card *> playerCards, QSet<Card *> dealerCards, bool callGame)
{
  calcValue(playerCards, playerValue_);
  calcValue(dealerCards, dealerValue_);

  if(playerValue_ > 21)
  {
    state_ = PLAYER_BUSTS;
    emit stateChanged(state_);
    return; // Check if player busts
  }

  if(playerValue_ == 21)   // Check if player wins
  {
    if(dealerValue_ == 21) // Check if it's a tie
    {
      state_ = ITS_A_TIE;
      emit stateChanged(state_);
      return;
    }
    state_ = PLAYER_WINS; // If not, player wins outright
    emit stateChanged(state_);
    return;
  }

  if(dealerValue_ > 21)   // If the player didn't bust, win outright, or tied with the dealer
                          // check if the dealer went bust
  {
    state_ = DEALER_BUSTS;
    emit stateChanged(state_);
    return;
  }

  // If the game wasn't called, normal play resumes
  if(!callGame)
  {
    state_ = CONTINUE_NORMAL_PLAY;
    emit stateChanged(state_);
    return;
  }
  else // Determine the winner and end it.
  {
    if(playerValue_ > dealerValue_)  state_ = PLAYER_WINS;
    if(dealerValue_ > playerValue_)  state_ = DEALER_WINS;
    if(dealerValue_ == playerValue_) state_ = ITS_A_TIE;

    emit stateChanged(state_);
    return;
  }
}

void BlackJackStateMachine::calcState(QSet<Card *> playerCards, QSet<Card *> dealerCards)
{
  calcState(playerCards, dealerCards, false);
}

// Runs through the provided container and calculates its value
void BlackJackStateMachine::calcValue(QSet<Card*> &container, int &value)
{
  value = 0;
  // Assumption: Aces always count 11 points, and are reduced if needed
  // to a score of 1 to prevent either player from going bust.
  int aceCount = 0;

  QSet<Card*>::iterator i = container.begin();

  while (i != container.end())
  {
    Card* card = *i;
    if(card->getValue() == 1 || card->getValue() == 11)
    {
      ++aceCount;
    }
    value += card->getValue();
    ++i;
  }

  if(value > 21) // Owner goes bust unless he has ACES
  {
    // We might be able to prevent the bust
    if(aceCount > 0)
    {
      // For as many ACES as the owner holds
      while(aceCount > 0)
      {
        value -= 10;  // Adjust ACE score from 11 to 1
        if(value <= 21) break; // until score dips below 22.
        --aceCount;   // Reduce the available number of ACES
      }
    }
  }

}

int BlackJackStateMachine::dealerValue() const
{
  return dealerValue_;
}

int BlackJackStateMachine::playerValue() const
{
  return playerValue_;
}
