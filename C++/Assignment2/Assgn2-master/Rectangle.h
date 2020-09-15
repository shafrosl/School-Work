//Rectangle.h

#ifndef Rectangle_H
#define Rectangle_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "ShapeTwoD.h"

using namespace std;

class Rectangle: public ShapeTwoD{
private:
   Vertex* vtxArray[4];
public:
   Rectangle(void);
   Rectangle(string, string, Vertex arr[4]);
   ~Rectangle();
   int setVertex(string, string, Vertex arr[4]);
   string getVertices();
   string getPtIn();
   string getPtOn();

   //virtual functions
   float computeArea();
   string toString();
   bool isPointInShape(Vertex);
   bool isPointOnShape(Vertex);
};

#endif
