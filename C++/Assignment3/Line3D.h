#ifndef LINE3D_H
#define LINE3D_H

#include "Line2D.h"
#include "Point3D.h"

class Line3D : public Line2D {
  Point3D* p3d;
private:
  Point3D p1;
  Point3D p2;

protected:
  double length;

  void setLength();

public:
  //accessors
  Point3D getP1();
  Point3D getP2();
  double getScalarValue();

  //mutators
  void setP1(Point3D p);
  void setP2(Point3D p);

  //constructors
  Line3D();
  Line3D(Point3D p1, Point3D p2);

  //overload
  friend std::ifstream& operator >> (std::ifstream& input, Line3D& l3d);
  friend std::ostream& operator << (std::ostream& output, Line3D& l3d);
  bool operator == (Line3D l3d);
  bool operator < (Line3D l3d);
  bool L3Dsortbyp1 (Line3D ln1, Line3D ln2);
  bool L3Dsortbyp2 (Line3D ln1, Line3D ln2);
  bool L3Dsortbyl (Line3D ln1, Line3D ln2);
};

#endif
