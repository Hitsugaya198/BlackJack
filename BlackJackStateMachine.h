#ifndef BLACKJACKSTATEMACHINE_H
#define BLACKJACKSTATEMACHINE_H

#include "GameStates.h"
#include "Card.h"
#include <QObject>

class BlackJackStateMachine : public QObject
{

    Q_OBJECT
  public:

    static BlackJackStateMachine* instance( )
    {
      if(instance_ == nullptr) instance_ = new BlackJackStateMachine();
      return instance_;
    }

    // This statemachine's primary concern is returning the state after
    // a change occurs.


    gameStates state() const;

    int playerValue() const;
    int dealerValue() const;

  signals:
    void stateChanged(gameStates state);

  public slots:
    void calcState(QSet<Card*> playerCards, QSet<Card*> dealerCards);
    void calcState(QSet<Card*> playerCards, QSet<Card*> dealerCards, bool callGame);


  private:
    BlackJackStateMachine(QObject *parent = 0);
    virtual ~BlackJackStateMachine();

    static BlackJackStateMachine* instance_;

    gameStates state_;
    void calcValue(QSet<Card *> &container, int &value);
    int playerValue_, dealerValue_;

};

#endif // BLACKJACKSTATEMACHINE_H
