#ifndef FACEVALUES
#define FACEVALUES

#include <QVector>

enum faceValues
{
  ace      = 11,
  two      = 2,
  three    = 3,
  four     = 4,
  five     = 5,
  six      = 6,
  seven    = 7,
  eight    = 8,
  nine     = 9,
  ten      = 10,
  jack     = 10,
  queen    = 10,
  king     = 10,
};

static QVector<faceValues> faceValuesVector =
    QVector<faceValues>{ace  ,
                        two  ,
                        three,
                        four ,
                        five ,
                        six  ,
                        seven,
                        eight,
                        nine ,
                        ten  ,
                        jack ,
                        queen,
                        king };

#endif // FACEVALUES

