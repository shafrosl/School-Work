#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <math.h>
#include <fstream>

#include "Point2D.h"

using namespace std;
  void Point2D::setDistFrOrigin() {
    distFrOrigin = sqrt((x*x) + (y*y));
  }

  //accessors
  int Point2D::getX() {
    return x;
  }

  int Point2D::getY() {
    return y;
  }

  double Point2D::getScalarValue() {
    setDistFrOrigin();
    return distFrOrigin;
  }

  //mutators
  void Point2D::setX(int x) {
    this->x = x;
  }

  void Point2D::setY(int y) {
    this->y = y;
  }

  //constructors
  Point2D::Point2D() {

  }

  Point2D::Point2D(int x, int y) {
    this->x = x;
    this->y = y;
  }

  ifstream& operator >> (ifstream& input, Point2D& p2d) {
  	input.ignore(2);
  	input >> p2d.x;
  	input.ignore(1);
  	input >> p2d.y;
  	input.ignore(1);
  	p2d.setDistFrOrigin();

  	return input;
  }

  ostream& operator << (ostream& output, Point2D& p2d) {
  	output << fixed << showpoint << setprecision(3);
  	output << "[";
  	output << right << p2d.x;
  	output << ", ";
  	output << right << p2d.y;
  	output << "]";
  	output << "   ";
    output << "distFrOrigin : ";
  	output << p2d.getScalarValue();

  	return output;
  }

  bool Point2D::operator == (Point2D p2d) {
  	return ((x == p2d.x) && (y == p2d.y));
  }

  bool Point2D::operator < (Point2D p2d) {
  	return ((x < p2d.x) || (y < p2d.y) || (distFrOrigin < p2d.distFrOrigin));
  }
