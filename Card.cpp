#include "Card.h"
#include <QDebug>

Card::Card(faces face, faceValues value, suits suit)
{
  face_ = face;
  value_ = value;
  suit_ = suit;
  loadFace();
  loadBack();
  qDebug() << "Card with face" << face_ << ", suit" << suit_ << ",and value" << value_ << "created";
}

Card::~Card()
{
  qDebug() << "Card with face" << face_ << ", suit" << suit_ << ",and value" << value_ << "Destroyed";
}

QPixmap Card::getFaceImage() const
{
  return faceImage_;
}

QPixmap Card::getBackImage() const
{
  return backImage_;
}


void Card::loadFace()
{
  // :/Images/Cards/Clubs/Three.png
  QString folder = suitNames.at(suit_);
  QString face = faceNames.at(face_);
  QString resPath = QString(":/Images/Cards/") + folder + QString("/") + face + QString(".png");

  QPixmap pm;
  pm.load(resPath, "PNG");
  faceImage_ = QPixmap{pm};
}

void Card::loadBack()
{
  QString resPath = QString(":/Images/Cards/Misc/CardBackBlue.png");

  QPixmap pm;
  pm.load(resPath, "PNG");
  backImage_ = QPixmap{pm};
}

