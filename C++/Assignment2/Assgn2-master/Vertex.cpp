//Vertex.cpp

#include "Vertex.h"

Vertex::Vertex(){
   aX = 0;
   aY = 0;
}

Vertex::Vertex(int bX, int bY){
   aX = bX;
   aY = bY;
}

/*Vertex::Vertex(Vertex newV){
   aX = newV->getVertexX();
   aY = newV->getVertexY();
}//*/

Vertex::~Vertex(){
   //destructor
}

int Vertex::setVertex(int bX, int bY){
   aX = bX;
   aY = bY;
}

int Vertex::getVertexX(){
   return aX;
}

int Vertex::getVertexY(){
   return aY;
}
 string Vertex::toString(){
    string allString = "";
    allString = "[" + to_string(aX) + "," + to_string(aY) + "]";
    return allString;
}
