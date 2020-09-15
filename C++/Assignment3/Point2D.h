#ifndef POINT2D_H
#define POINT2D_H

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <math.h>
#include <fstream>

class Point2D {
//friend class Line2D;
protected:
  int x, y;
  double distFrOrigin;
  void setDistFrOrigin();

public:
  //accessors
  int getX();
  int getY();
  double getScalarValue();

  //mutators
  void setX(int x);
  void setY(int y);

  //constructors
  Point2D();
  Point2D(int x, int y);

  //overload
  friend std::ifstream& operator >> (std::ifstream& input, Point2D& p2d);
  friend std::ostream& operator << (std::ostream& output, Point2D& p2d);
  bool operator == (Point2D p2d);
  bool operator < (Point2D p2d);
  bool P2Dsortbyx (Point2D p1, Point2D p2);
  bool P2Dsortbyy (Point2D p1, Point2D p2);
  bool P2Dsortbys (Point2D p1, Point2D p2);
};

#endif
