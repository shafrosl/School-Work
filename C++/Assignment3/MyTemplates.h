#ifndef MYTEMPLATES_H
#define MYTEMPLATES_H

#include <cmath>
#include <math.h>

#include "MyTemplates.h"
#include "Point2D.h"
#include "Point3D.h"
#include "Line2D.h"
#include "Line3D.h"

template <class T>
double scalar_difference(T i, T j) {
  double diff = i.getScalarValue() - j.getScalarValue();

  return std::abs(diff);
}

template <class T>
bool equals(T i, T j) {
  if (i == j) {
    return true;
  }
  else {
    return false;
  }
}

#endif
