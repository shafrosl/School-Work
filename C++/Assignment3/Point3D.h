#ifndef POINT3D_H
#define POINT3D_H

#include "Point2D.h"

class Point3D : public Point2D {
//friend class Line3D;
protected:
  int z;
  void setDistFrOrigin();

public:
  //accessor
  int getZ();

  //mutator
  void setZ(int z);
  double getScalarValue();

  //constructors
  Point3D();
  Point3D(int x, int y, int z);

  //overload
  friend std::ifstream& operator >> (std::ifstream& input, Point3D& p3d);
  friend std::ostream& operator << (std::ostream& output, Point3D& p3d);

  bool operator == (Point3D p3d);
  bool operator < (Point3D p3d);
  bool P3Dsortbyx (Point3D p1, Point3D p2);
  bool P3Dsortbyy (Point3D p1, Point3D p2);
  bool P3Dsortbyz (Point3D p1, Point3D p2);
  bool P3Dsortbys (Point3D p1, Point3D p2);
};

#endif
