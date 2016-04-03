#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow),
  noCard_(),
  openSpace_(),
  banner_(),
  playerScore_(),
  dealerScore_()
{
  ui->setupUi(this);

  // Allow gui to create an object of the BlackJack Game.
  blackJack_ = new BlackJack();

  // Hide buttons until new game is started.
  ui->hitMeButton_->hide();
  ui->callItButton_->hide();

  setWindowTitle("BlackJack by Louis Parkin");

  QPixmap icon;
  icon.load(":/Images/Cards/Misc/BlackjackIcon.png", "PNG");

  setWindowIcon(QIcon(icon));

  resetCards();

  connect(blackJack_, SIGNAL(stateChanged(gameStates)), this, SLOT(stateChangedSlot(gameStates)));
}

void MainWindow::resetCards()
{
  noCard_.load(":/Images/Cards/Misc/CardBackBlue.png","PNG");
  openSpace_.load(":/Images/Cards/Misc/OpenSpace.png","PNG");
  banner_.load(":/Images/Cards/Misc/OpenBanner.png","PNG");

  ui->card1_->setPixmap(noCard_);
  ui->card2_->setPixmap(noCard_);
  ui->card3_->setPixmap(openSpace_);
  ui->card4_->setPixmap(openSpace_);
  ui->card5_->setPixmap(openSpace_);
  ui->card6_->setPixmap(openSpace_);

  ui->dealerCard1_->setPixmap(noCard_);
  ui->dealerCard2_->setPixmap(noCard_);
  ui->dealerCard3_->setPixmap(openSpace_);
  ui->dealerCard4_->setPixmap(openSpace_);
  ui->dealerCard5_->setPixmap(openSpace_);
  ui->dealerCard6_->setPixmap(openSpace_);

  ui->statusImage_->setPixmap(banner_);
}



MainWindow::~MainWindow()
{
  delete ui;
  delete blackJack_;
}


void MainWindow::initDeck_()
{
  if(blackJack_ != nullptr)
  {
    delete blackJack_;
  }
  blackJack_ = new BlackJack();
  connect(blackJack_, SIGNAL(stateChanged(gameStates)), this, SLOT(stateChangedSlot(gameStates)));
  resetCards();
}

void MainWindow::deal_()
{
  if(blackJack_ != nullptr)
  {
    QPair<Card*,Card*> x = blackJack_->deal(PLAYER);

    ui->card1_->setPixmap(x.first->getFaceImage());
    ui->card2_->setPixmap(x.second->getFaceImage());

    x = blackJack_->deal(DEALER);

    ui->dealerCard1_->setPixmap( x.first->getBackImage());
    ui->dealerCard2_->setPixmap(x.second->getBackImage());
  }
}

void MainWindow::shuffle_()
{
  if(blackJack_ != nullptr)
  {
    blackJack_->shuffleDeck();
  }
}

void MainWindow::on_hitMeButton__clicked()
{
  if(blackJack_ != nullptr)
  {
    // Create a PixmapWidget pointer.
    PixmapWidget *widget;

    // Get a card from the deck.
    Card* temp = blackJack_->hitMe(PLAYER, true);

    // Check the player Card Count to determine
    // which widget to give an image to.
    switch(blackJack_->getPlayerCardCount())
    {
      case 3: widget = ui->card3_; break;
      case 4: widget = ui->card4_; break;
      case 5: widget = ui->card5_; break;
      case 6: widget = ui->card6_; break;
      default: return;
    }
    // And set the image
    widget->setPixmap(temp->getFaceImage());

    if(blackJack_->getDealerCardsValue() <= 16)
    {
      temp = blackJack_->hitMe(DEALER, true);
      switch(blackJack_->getDealerCardCount())
      {
        case 3: widget = ui->dealerCard3_; break;
        case 4: widget = ui->dealerCard4_; break;
        case 5: widget = ui->dealerCard5_; break;
        case 6: widget = ui->dealerCard6_; break;
        default: return;
      }
      widget->setPixmap(temp->getBackImage());
    }
  }
}

void MainWindow::endGame(gameStates state)
{
  switch(state)
  {
    case DEALER_WINS  : banner_.load(":/Images/Cards/Misc/LoseBanner.png","PNG");   dealerScore_++; break;
    case PLAYER_BUSTS : banner_.load(":/Images/Cards/Misc/BustedBanner.png","PNG"); dealerScore_++; break;
    case DEALER_BUSTS :
    case PLAYER_WINS  : banner_.load(":/Images/Cards/Misc/WinBanner.png","PNG");    playerScore_++; break;
    case CONTINUE_NORMAL_PLAY :
    case ITS_A_TIE    : banner_.load(":/Images/Cards/Misc/TieBanner.png","PNG");/*playerScore_++;*/ break;
  }

  flipDealerCards();
  ui->playerScore_->display(playerScore_);
  ui->dealerScore_->display(dealerScore_);
  ui->statusImage_->setPixmap(banner_);
  ui->hitMeButton_->hide();
  ui->callItButton_->hide();
}

void MainWindow::on_action_Exit_triggered()
{
  QApplication::exit(0);
}

void MainWindow::newGame()
{
  initDeck_();
  shuffle_();
  deal_();
  ui->hitMeButton_->show();
  ui->callItButton_->show();
}

void MainWindow::flipDealerCards()
{
  PixmapWidget *widget;
  QSet<Card*> dealerCards = blackJack_->getDealerCards();
  QSet<Card*>::iterator i = dealerCards.begin();
  int count = 0;
  while(i != dealerCards.end())
  {
    switch(count)
    {
      case 0: widget = ui->dealerCard1_; break;
      case 1: widget = ui->dealerCard2_; break;
      case 2: widget = ui->dealerCard3_; break;
      case 3: widget = ui->dealerCard4_; break;
      case 4: widget = ui->dealerCard5_; break;
      case 5: widget = ui->dealerCard6_; break;
      default: return;
    }
    count++;
    Card* card = *i; ++i;
    widget->setPixmap(card->getFaceImage());
  }
}

void MainWindow::on_callItButton__clicked()
{
  blackJack_->updateState(true);
}

void MainWindow::on_newGameButton__clicked()
{
  setWindowTitle("BlackJack by Louis Parkin");
  newGame();
}

void MainWindow::stateChangedSlot(gameStates state)
{
  if(state != CONTINUE_NORMAL_PLAY)
  {
    endGame(state);
  }
}
