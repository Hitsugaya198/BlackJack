#ifndef SUITS
#define SUITS

#include <QStringList>

enum suits
{
  CLUBS = 0,
  DIAMONDS,
  HEARTS,
  SPADES,
  max_suits
};

static QStringList suitNames = QStringList{
    "Clubs",
    "Diamonds",
    "Hearts",
    "Spades"};

#endif // SUITS

