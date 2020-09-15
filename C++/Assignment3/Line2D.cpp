#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <math.h>
#include <fstream>

#include "Line2D.h"

using namespace std;
  //accessors
  Point2D Line2D::getP1() {
    return p1;
  }

  Point2D Line2D::getP2() {
    return p2;
  }

  double Line2D::getScalarValue() {
    setLength();
    return length;
  }

  //mutators
  void Line2D::setP1(Point2D p1) {
    this->p1 = p1;
  }

  void Line2D::setP2(Point2D p2) {
    this->p2 = p2;
  }

  void Line2D::setLength() {
    length = sqrt(pow((p1.getX() - p2.getX()), 2) + pow((p1.getY() - p2.getY()), 2));
  }

  //constructors
  Line2D::Line2D() : p1(), p2() {

  }

  Line2D::Line2D(Point2D p1, Point2D p2) : p1(p1), p2(p2) {

  }

  ifstream& operator >> (ifstream& input, Line2D& l2d) {
  	input >> l2d.p1;
  	input.ignore(1);
  	input >> l2d.p2;
  	l2d.setLength();

  	return input;
  }

  ostream& operator << (ostream& output, Line2D& l2d) {
  	output << fixed << showpoint << setprecision(3);
  	output << "( [";
  	output << l2d.p1.getX();
  	output << ", ";
  	output << l2d.p1.getY();
  	output << "], ";
  	output << "distFrOrigin : ";
    output << l2d.p1.getScalarValue();
  	output << " to [";
  	output << l2d.p2.getX();
  	output << ", ";
  	output << l2d.p2.getY();
  	output << "], ";
    output << "distFrOrigin : ";
    output << l2d.p2.getScalarValue();
    output << " ), ";
    output << "length : ";
  	output << l2d.getScalarValue();

  	return output;
  }

  bool Line2D::operator == (Line2D l2d) {
  	return ((p1 == l2d.p1) && (p2 == l2d.p2));
  }

  bool Line2D::operator < (Line2D l2d) {
  	return ((p1.getX() < l2d.p1.getX()) || ((p1.getX() == l2d.p1.getX()) && (p1.getY() < l2d.p1.getY())) || (length < l2d.length) || (p2.getX() < l2d.p2.getX()) || ((p2.getX() == l2d.p2.getX()) && (p2.getY() < l2d.p2.getY())));
  }
