//ShapeTwoD.h
//Contains only the base attributes, works only as a superclass.
#ifndef ShapeTwoD_H
#define ShapeTwoD_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cmath>
#include "Vertex.h"


using namespace std;

class ShapeTwoD{
protected:
   string name;
   int noOfVertices;
   string spaceType;
public:
   ShapeTwoD();
   ShapeTwoD(string, int, string);
   virtual ~ShapeTwoD();
   int setValues(string, int, string);
   string getName();
   int getNoOfVertices();
   string getspaceType();
   string basicToString();
   virtual float computeArea();
   virtual string toString();
   virtual bool isPointInShape(Vertex);
   virtual bool isPointOnShape(Vertex);

};

#endif
