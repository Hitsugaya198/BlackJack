#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "BlackJack.h"


namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();


  private slots:
    // File menu action -> Exit.
    void on_action_Exit_triggered();

    // Buttons on screen, "hit me" and "call it".
    void on_hitMeButton__clicked();
    void on_callItButton__clicked();
    void on_newGameButton__clicked();

    void stateChangedSlot(gameStates state);

  private:
    Ui::MainWindow *ui;    // Raw Ui::MainWindow pointer, deleted by destructor.
    BlackJack *blackJack_; // Raw BlackJack pointer, deleted by destructor.

    QPixmap noCard_, openSpace_, banner_; // Concrete instances, automatically scoped.

    int playerScore_, dealerScore_;

    void initDeck_();  // Re-initialises the cards (creates new cards) and repopulates the containers.
    void deal_();      // Deals the cards.
    void shuffle_();   // Shuffles the deck.
    void resetCards(); // Resets the visual components back to starting positions.
    void endGame(gameStates state);


    void flipDealerCards();            // Make the faces of the dealer's cards visible.
    void newGame();
};

#endif // MAINWINDOW_H
