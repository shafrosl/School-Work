#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <math.h>
#include <fstream>

#include "Line2D.h"
#include "Line3D.h"

using namespace std;
  void Line3D::setLength() {
    length = sqrt(pow((p1.getX() - p2.getX()), 2) + pow((p1.getY() - p2.getY()), 2) + pow((p1.getZ() - p2.getZ()), 2));
  }

  //accessors
  Point3D Line3D::getP1() {
    return p1;
  }

  Point3D Line3D::getP2() {
    return p2;
  }

  double Line3D::getScalarValue() {
    setLength();
    return length;
  }

  //mutators
  void Line3D::setP1(Point3D p) {
    this->p1 = p;
  }

  void Line3D::setP2(Point3D p) {
    this->p2 = p;
  }

  //constructors
  Line3D::Line3D() : Line2D(), p1(), p2() {

  }

  Line3D::Line3D(Point3D p1, Point3D p2) : Line2D(p1, p2), p1(p1), p2(p2) {

  }

  ifstream& operator >> (ifstream& input, Line3D& l3d) {
  	input >> l3d.p1;
  	input.ignore(1);
  	input >> l3d.p2;
  	l3d.setLength();
  	return input;
  }

  ostream& operator << (ostream& output, Line3D& l3d) {
  	output << fixed << showpoint << setprecision(3);
  	output << "( [";
  	output << l3d.p1.getX();
  	output << ", ";
  	output << l3d.p1.getY();
  	output << ", ";
  	output << l3d.p1.getZ();
  	output << "], ";
  	output << "distFrOrigin : ";
    output << l3d.p1.getScalarValue();
  	output << " to [";
  	output << l3d.p2.getX();
  	output << ", ";
  	output << l3d.p2.getY();
  	output << ", ";
  	output << l3d.p2.getZ();
  	output << "], ";
    output << "distFrOrigin : ";
    output << l3d.p2.getScalarValue();
    output << " ), ";
    output << "length : ";
  	output << l3d.getScalarValue();

  	return output;
  }

  bool Line3D::operator == (Line3D l3d) {
    return ((p1 == l3d.p1) && (p2 == l3d.p2));
  }

  bool Line3D::operator < (Line3D l3d) {
    return (length < l3d.length);
  }
