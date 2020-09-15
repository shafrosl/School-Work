//Rectangle.cpp

#include "Rectangle.h"

Rectangle::Rectangle(void){
   name = "";
   noOfVertices = 4;
   spaceType =  "NS";
   for (int i = 0; i < noOfVertices; i++) {
      vtxArray[i] = new Vertex();
   }
}

Rectangle::Rectangle(string setName, string setST, Vertex newVArr[4]){
   name = setName;
   noOfVertices = 4;
   spaceType =  setST;
   for (int i = 0; i < noOfVertices; i++) {
      vtxArray[i] = new Vertex(newVArr[i]);
   }
   cout << toString() << endl;
}

Rectangle::~Rectangle(){
   //destructor
   cout << "Rect dst" << endl;
}

int Rectangle::setVertex(string setName, string setST, Vertex newVArr[4]){
   name = setName;
   noOfVertices = 4;
   spaceType =  setST;
   for (int i = 0; i < noOfVertices; i++) {
      vtxArray[i] = new Vertex(newVArr[i]);
   }
}

string Rectangle::getVertices(){
   string vtxString = "Vertices:\n";
   for (int i = 0; i < noOfVertices; i++) {
      if (i == 0) {
         vtxString = "Point[" + to_string(i) + "]: " + vtxArray[i]->toString();
      } else {
         vtxString = vtxString + "\nPoint[" + to_string(i) + "]: " + vtxArray[i]->toString();
      }
   }
   return vtxString;
}

string Rectangle::getPtIn(){
   string result = "";
   int xMin, yMin, xMax, yMax;
   int xRange, yRange;

   //Get min/max range of shape
   for (int i = 0; i < noOfVertices; i++) {
      int j = i + 1;
      if (i == noOfVertices-1) {
         j = 0;
      }
      int aX = vtxArray[i]->getVertexX();
      int bX = vtxArray[j]->getVertexX();
      int aY = vtxArray[i]->getVertexY();
      int bY = vtxArray[j]->getVertexY();

      if (i == 0) {
         xMin = aX;
         xMax = aX;
         yMin = aY;
         yMax = aY;
      }

      //Gets the max and min points for the shape
      if (aX < xMin) {
         xMin = aX;
      } else if (bX < xMin) {
         xMin = bX;
      }

      if (aY < yMin) {
         yMin = aY;
      } else if (bY < yMin) {
         yMin = bY;
      }

      if (aX > xMax) {
         xMax = aX;
      } else if (bX > xMax) {
         xMax = bX;
      }

      if (aY > yMax) {
         yMax = aY;
      } else if (bY > yMax) {
         yMax = bY;
      }
   } // END of for loop

   //Get number of points in Rectangle
   xRange = xMax-xMin-1;
   yRange = yMax-yMin-1;
   if (!xRange > 0) {
      return "No Pts";
   }

   if (!yRange > 0) {
      return "No Pts";
   }
   int inShapeSize = xRange * yRange;
   cout << "inShapeSize: " << inShapeSize << endl;

   Vertex inShapeVtxArr[inShapeSize];
   int inShapeItr = 0;

   //Obtains points in shape from top-down, left-right
   for (int y = 1; y < yRange+1; y++) {
      for (int x = 1; x < xRange+1; x++) {
         inShapeVtxArr[inShapeItr] = Vertex(xMin+x, yMin+y);
         inShapeItr++;
         if (inShapeItr > inShapeSize) {
            cout << "For loop should be ending now." << endl;
         }
      }
   }

   for (int i = 0; i < inShapeSize; i++) {
      if (i == 0) {
         result = "[" + to_string(inShapeVtxArr[i].getVertexX()) + "," + to_string(inShapeVtxArr[i].getVertexY()) + "]";
      } else {
         result = result + ", [" + to_string(inShapeVtxArr[i].getVertexX()) + "," + to_string(inShapeVtxArr[i].getVertexY()) + "]";
      }
   }

   return result;
}

string Rectangle::getPtOn(){
   int edgePts = 0; // count number of points between vertices, excluding vertices

   // Counts points on each edges, excluding the vertices
   for (int i = 0; i < noOfVertices; i++){
      int j = i + 1;
      if (i == noOfVertices-1) {
         j = 0;
      }

      int aX = vtxArray[i]->getVertexX();
      int bX = vtxArray[j]->getVertexX();
      int aY = vtxArray[i]->getVertexY();
      int bY = vtxArray[j]->getVertexY();

      if (aX == bX) {
         edgePts = edgePts + abs(aY - bY) - 1;
      } else if (aY == bY) {
         edgePts = edgePts + abs(aX - bX) - 1;
      } else {
         cout << "Error: shape cannot be computed!" << endl;
         return "1";
      }
   } // end for loop

   if (!edgePts > 0) {
      cout << "Error: No points on shape!" << endl;
      return "1";
   }

   cout << "edgePts: " << edgePts << endl;
   Vertex totalVTXArr[edgePts];
   int totalInt = 0;
   for (int i = 0; i < noOfVertices; i++) {
      int j = i + 1;
      if (i == noOfVertices-1) {
         j = 0;
      }

      int pointDist = 0;
      int aX = vtxArray[i]->getVertexX();
      int bX = vtxArray[j]->getVertexX();
      int aY = vtxArray[i]->getVertexY();
      int bY = vtxArray[j]->getVertexY();
      string XorY;//Checks which axis is the line parallel to

      //Checks for number of coodinates which describe the edges of the Rectangle
      if (aX == bX) {
         pointDist = abs(aY - bY);
         XorY = "X";
      } else if (aY == bY) {
         pointDist = abs(aX - bX);
         XorY = "Y";
      } else {
         cout << "Error: Side is slanted!" << endl;
         return "1";
      }

      if (pointDist == 0) {
         cout << "Error: Side has no points!" << endl;
         return "1";
      }
      // cout << "pointDist: " << pointDist << endl;
      if (XorY == "X") { //Parallel to the X-axis
         for (int p = 1; p < pointDist; p++) {
            if (aY < bY) {
               // cout << "aX: " << aX << ", aY+p: " << aY+p << "\n";
               totalVTXArr[totalInt] = Vertex(aX, aY+p);
               totalInt++;
            } else if (aY > bY) {
               // cout << "aX: " << aX << ", bY+p: " << bY+p << "\n";
               totalVTXArr[totalInt] = Vertex(aX, bY+p);
               totalInt++;
            } else {
               printf("Huh?\n");
            }
         }
      } else if (XorY == "Y") { //Parallel to the Y-axis
         for (int p = 1; p < pointDist; p++) {
            if (aX < bX) {
               // cout << "aX+p: " << aX+p << ", aY: " << aY << "\n";
               totalVTXArr[totalInt] = Vertex(aX+p, aY);
               totalInt++;
            } else if (aX > bX) {
               // cout << "bX+p: " << bX+p << ", aY: " << aY << "\n";
               totalVTXArr[totalInt] = Vertex(bX+p, aY);
               totalInt++;
            } else {
               printf("Huh?\n");
            }
         }
      }
      //Next edge
   }

   string result = "";
   for (int i = 0; i < edgePts; i++) {
      if (i == 0) {
         result = "[" + to_string(totalVTXArr[i].getVertexX()) + "," + to_string(totalVTXArr[i].getVertexY()) + "]";
      } else {
         result = result + ", [" + to_string(totalVTXArr[i].getVertexX()) + "," + to_string(totalVTXArr[i].getVertexY()) + "]";
      }
   }
   return result;
}

float Rectangle::computeArea(){
   float rctArea = 0.0;
   int j = noOfVertices-1;
   for (int i = 0; i < noOfVertices; i++) {
      rctArea += (vtxArray[j]->getVertexX() + vtxArray[i]->getVertexX()) * (vtxArray[j]->getVertexY() - vtxArray[i]->getVertexY());
      j = i;
   }

   rctArea = abs(rctArea/2.0);
   return rctArea;
}

string Rectangle::toString(){
   string allString = "";
   allString = basicToString();
   allString = allString + "\n\nArea:\n" + to_string(computeArea()) + " million KM^2\n\nVertices:\n" + getVertices() + "\n\nPoints on shape:\n" + getPtOn() + "\n\nPoints in shape:\n" + getPtIn();
   return allString;
}

bool Rectangle::isPointInShape(Vertex vtx){
   int pointX = vtx.getVertexX();
   int pointY = vtx.getVertexY();
   int xMin, yMin, xMax, yMax;
   int noOfPts = 0;

   //Get range of pts
   for (int i = 0; i < noOfVertices; i++) {
      int j = i + 1;
      if (i == noOfVertices) {
         j = 0;
      }
      int aX = vtxArray[i]->getVertexX();
      int bX = vtxArray[j]->getVertexX();
      int aY = vtxArray[i]->getVertexY();
      int bY = vtxArray[j]->getVertexY();

      if (i == 0) {
         xMin = aX;
         xMax = aX;
         yMin = aY;
         yMax = aY;
      }

      //Gets the max and min points for the shape
      if (aX < xMin) {
         xMin = aX;
      } else if (bX < xMin) {
         xMin = bX;
      }

      if (aY < yMin) {
         yMin = aY;
      } else if (bY < yMin) {
         yMin = bY;
      }

      if (aX > xMax) {
         xMax = aX;
      } else if (bX > xMax) {
         xMax = bX;
      }

      if (aY > yMax) {
         yMax = aY;
      } else if (bY > yMax) {
         yMax = bY;
      }
   } // END of for loop

   if (pointX <= xMin || pointY <= yMin || pointX >= xMax || pointY >= yMax) {
      return false;
   } else {
      return true;
   }

   return false;
}

bool Rectangle::isPointOnShape(Vertex vtx){
   //TODO
   int pointX = vtx.getVertexX();
   int pointY = vtx.getVertexY();
   for (int i = 0; i < noOfVertices; i++) {
      int j = i + 1;
      if (i == noOfVertices-1) {
         j = 0;
      }

      int pointDist = 0;
      int aX = vtxArray[i]->getVertexX();
      int bX = vtxArray[j]->getVertexX();
      int aY = vtxArray[i]->getVertexY();
      int bY = vtxArray[j]->getVertexY();
      string XorY;//Checks which axis is the line parallel to

      //If point is on vertices
      if (pointX == aX && pointY == aY) {
         cout << "ON VERTEX: Entry [" << pointX << ":" << pointY << "]: " << aX << ":" << aY << endl;
         return false;
      } else if (pointX == bX && pointY == bY) {
         cout << "ON VERTEX: Entry [" << pointX << ":" << pointY << "]: " << bX << ":" << bY << endl;
         return false;
      }
      //Checks for number of points which describe the edges of the Rectangle
      if (aX == bX) {
         pointDist = abs(aY - bY);
         XorY = "X";
      } else if (aY == bY) {
         pointDist = abs(aX - bX);
         XorY = "Y";
      } else {
         cout << "Error: shape cannot be computed!" << endl;
         return false;
      }

      if (pointDist == 0) {
         cout << "Error: shape cannot be computed!" << endl;
         return false;
      }

      //Vertex tmpVTXArr[pointDist];
      if (XorY == "X" && pointX == aX) {
         for (int p = 0; p < pointDist; p++) {
            if (aY < bY) {
               if (pointY == aY+p) {
                  return true;
               }
            } else if (aY > bY) {
               if (pointY == bY+p) {
                 return true;
              }
            }
         }
      } else if (XorY == "Y" && pointY == aY) {
         for (int p = 0; p < pointDist; p++) {
            if (aX < bX) {
               if (pointX == aX+p) {
                  return true;
               }
            } else if (aX > bX) {
               if (pointX == bX+p) {
                 return true;
              }
            }
         }
      }

      //Next edge
   } //end for loop
   cout << "C4" << endl;
   cout << "Point is not on shape!" << endl;
   return false;
}
