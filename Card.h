#ifndef CARD_H
#define CARD_H

#include "Faces.h"
#include "FaceValues.h"
#include "Suits.h"
#include <QPixmap>

class Card
{
  public:
    Card(faces face, faceValues value, suits suit);
    ~Card();

    // A card has a face, a suit and a value

    faces getFace()       { return face_;  }
    faceValues getValue() { return value_; }
    suits getSuit()       { return suit_;  }

    QPixmap getFaceImage() const;
    QPixmap getBackImage() const;

  private:
    faces face_;
    faceValues value_;
    suits suit_;

    QPixmap faceImage_;
    QPixmap backImage_;

    void loadFace();
    void loadBack();
};

#endif // CARD_H
