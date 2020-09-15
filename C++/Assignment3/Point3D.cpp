#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <math.h>
#include <fstream>

#include "Point3D.h"

using namespace std;
  void Point3D::setDistFrOrigin() {
    distFrOrigin = sqrt((x*x) + (y*y) + (z*z));
  }

  //accessor
  int Point3D::getZ() {
    return z;
  }

  //mutator
  void Point3D::setZ(int z) {
    this->z = z;
  }

  double Point3D::getScalarValue() {
    setDistFrOrigin();
    return distFrOrigin;
  }

  //constructors
  Point3D::Point3D() : Point2D() {

  }

  Point3D::Point3D(int x, int y, int z) : Point2D(x, y) {
    this->z = z;
  }

  ifstream& operator >> (ifstream& input, Point3D& p3d) {
  	input.ignore(2);
  	input >> p3d.x;
  	input.ignore(1);
  	input >> p3d.y;
  	input.ignore(1);
  	input >> p3d.z;
  	input.ignore(1);
  	p3d.setDistFrOrigin();

  	return input;
  }

  ostream& operator << (ostream& output, Point3D& p3d) {
  	output << fixed << showpoint << setprecision(3);
  	output << "[";
  	output << p3d.x;
  	output << ", ";
  	output << p3d.y;
  	output << ", ";
  	output << p3d.z;
  	output << "]";
  	output << "   ";
    output << "distFrOrigin : ";
  	output << p3d.getScalarValue();

  	return output;
  }

  bool Point3D::operator == (Point3D p3d) {
  	return ((x == p3d.x) && (y == p3d.y) && (z == p3d.z));
  }

  bool Point3D::operator < (Point3D p3d) {
  	return ((x < p3d.x) || (y < p3d.y) || (distFrOrigin < p3d.distFrOrigin));
  }
