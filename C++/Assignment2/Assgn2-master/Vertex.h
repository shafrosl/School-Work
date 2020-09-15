//Vertex.h
#ifndef Vertex_H
#define Vertex_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

class Vertex{
private:
   int aX, aY;
public:
   Vertex();
   Vertex(int, int);
   //Vertex(Vertex);
   ~Vertex();
   int setVertex(int, int);
   int getVertexX();
   int getVertexY();
   string toString();
};

#endif
