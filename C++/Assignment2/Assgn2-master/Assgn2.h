//Assgn2.h
#ifndef Assgn2_H
#define Assgn2_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "Vertex.h"
#include "ShapeTwoD.h"
#include "Rectangle.h"
#include "Cross.h"

using std::cin;
using std::endl;

void printWelcomeMsg();
void printMenu();
int startMenu();
int addData();
int computeAllArea();
int printReport();
int printAllData();
int printSortedData();
int isPointOn();
int isPointIn();

ShapeTwoD *globalS2D[100];

int GS2Dcap = 0;

#endif
