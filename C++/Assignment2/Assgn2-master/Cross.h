//Cross.h

#ifndef Cross_H
#define Cross_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "ShapeTwoD.h"

using namespace std;

class Cross: public ShapeTwoD{
private:
   Vertex* vtxArray[12];
public:
   Cross(void);
   Cross(string, string, Vertex arr[12]);
   ~Cross();
   int setVertex(string, string, Vertex arr[12]);
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
