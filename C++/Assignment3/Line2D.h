#ifndef LINE2D_H
#define LINE2D_H

#include "Point2D.h"

class Line2D {
  Point2D* p2d;
private:
  Point2D p1;
  Point2D p2;

protected:
  double length;
  void setLength();

public:
  //accessors
  Point2D getP1();
  Point2D getP2();
  double getScalarValue();

  //mutators
  void setP1(Point2D p1);
  void setP2(Point2D p2);

  //constructors
  Line2D();
  Line2D(Point2D p1, Point2D p2);
  friend std::ifstream& operator >> (std::ifstream& input, Line2D& l2d);
  friend std::ostream& operator << (std::ostream& output, Line2D& l2d);
  bool operator == (Line2D l2d);
  bool operator < (Line2D l2d);
  bool L2Dsortbyp1 (Line2D ln1, Line2D ln2);
  bool L2Dsortbyp2 (Line2D ln1, Line2D ln2);
  bool L2Dsortbyl (Line2D ln1, Line2D ln2);
};

#endif
