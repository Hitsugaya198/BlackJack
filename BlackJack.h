#ifndef BLACKJACK_H
#define BLACKJACK_H

#include <QPair>
#include <QTimer>
#include <QObject>
#include "Deck.h"
#include "Participants.h"
#include "BlackJackStateMachine.h"

class BlackJack : public QObject
{
    Q_OBJECT
  public:
    BlackJack();
    ~BlackJack();

    QPair<Card *, Card *> deal(participants whoDunnit);
    Card *hitMe(participants whoDunnit, bool triggerUpdate = false);

    void shuffleDeck();

    int getCardCount() const;
    int getPlayerCardCount() const;
    int getDealerCardCount() const;
    int getPlayerCardsValue() const;
    int getDealerCardsValue() const;

    QSet<Card *> getDealerCards() const;

  private:
    Deck * deck_;
    int playerCardCount_;
    int dealerCardCount_;
//    BlackJackStateMachine *stateMachine_;
    QSet<Card*> playerCards_, dealerCards_;  // The QSet is concrete, and the pointers don't belong to him.

    void addCards(participants whoDunnit, QPair<Card *, Card *> pair);
    void addCard(participants whoDunnit, Card *card);

  signals:
    void endGame(gameStates state); // Game is over.
    void stateChanged(gameStates state);

  private slots:
    void updateState();
  public slots:
    void updateState(bool callGame);
    void stateChangedSlot(gameStates state);

};

#endif // BLACKJACK_H

