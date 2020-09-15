//ShapeTwoD.cpp

#include "ShapeTwoD.h"

ShapeTwoD::ShapeTwoD(){
   name = "";
   noOfVertices = 0;
   spaceType =  "NS";
}

ShapeTwoD::ShapeTwoD(string newName, int newNo, string newST){
   name = newName;
   noOfVertices = newNo;
   spaceType = newST;
}

ShapeTwoD::~ShapeTwoD(){
   //destructor
}

int ShapeTwoD::setValues(string newName, int newNo, string newST){
   name = newName;
   noOfVertices = newNo;
   spaceType = newST;
}

string ShapeTwoD::getName(){
   return name;
}

int ShapeTwoD::getNoOfVertices(){
   return noOfVertices;
}

string ShapeTwoD::getspaceType(){
   return spaceType;
}

string ShapeTwoD::basicToString(){
   string allString = "";
   allString = "Name: " + name + "\nNo. of Vertices: " + to_string(noOfVertices) + "\nSpace Type: " + spaceType;
   return allString;
}

float ShapeTwoD::computeArea(){
   cout << "This should not be printed: ShapeTwoD::computeArea()"<< endl;
   return 0.0;
}

string ShapeTwoD::toString(){
   cout << "This should not be printed: ShapeTwoD::toString()"<< endl;
   return basicToString();
}

bool ShapeTwoD::isPointInShape(Vertex vtx){
   cout << "This should not be printed: ShapeTwoD::isPointInShape()"<< endl;

   return false;
}

bool ShapeTwoD::isPointOnShape(Vertex vtx){
   cout << "This should not be printed: ShapeTwoD::isPointOnShape()"<< endl;
   //TODO
   int pointX = vtx.getVertexX();
   int pointY = vtx.getVertexY();
   return false;
}
