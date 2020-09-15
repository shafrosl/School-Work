//g++ -std=c++11 Main.cpp -o A2.exe
//./A2.exe

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <math.h>
#include <stdio.h>
#include <ctype.h>
using namespace std;

class ShapeTwoD {
protected:
  string name;
  bool containsWarpSpace;
  double area;
  int id;

public:
  //constructors
  ShapeTwoD() {

  }

  ShapeTwoD(string name, bool containsWarpSpace) {
    this->name = name;
    this->containsWarpSpace = containsWarpSpace;
  }

  //destructor
  virtual ~ShapeTwoD (){

  }

  //accessors
  int getID() {
    return id;
  }

  string getName() {
    return name;
  }

  bool getContainsWarpSpace() {
    return containsWarpSpace;
  }

  double getArea() {
    return area;
  }

  //mutators
  void setID(int id) {
    this->id = id;
  }

  void setName(string name) {
    this->name = name;
  }

  void setContainsWarpSpace(bool containsWarpSpace) {
    this->containsWarpSpace = containsWarpSpace;
  }

  void setArea(double area) {
    this->area = area;
  }

  virtual string toString() {
    stringstream ss;

    //prints the ID, name and special type of shape
    ss << "Shape [" << getID() << "]" << endl
       << "Name: " << getName() << endl
       << "Special Type: ";

       if (getContainsWarpSpace()) {
         ss << "WS" << endl;
       }
       else {
         ss << "NS" << endl;
       }

    return ss.str();
  }

  virtual double computeArea() {
    return 0.00;
  }

  virtual bool isPointOnShape(int x, int y) {
    return false;
  }

  virtual bool isPointInShape(int x, int y) {
    return false;
  }
};

class Cross : public ShapeTwoD {
private:
  int x[12];
  int y[12];
  int maxx = -1000;
  int maxy = -1000;
  int minx = 1000;
  int miny = 1000;

  // to find minimum and maximum of point of each shape
  void findmm() {
    for (int i = 0; i < 12; i++) {
      if ((x[i]) > maxx) {
        maxx = x[i];
      }
      if ((x[i]) < minx) {
        minx = x[i];
      }
      if ((y[i]) > maxy) {
        maxy = y[i];
      }
      if ((y[i]) < miny) {
        miny = y[i];
      }
    }
  }

public:
  //accessors
  int getX(int pos) {
    return x[pos];
  }

  int getY(int pos) {
    return y[pos];
  }

  //mutators
  void setX(int c, int pos) {
    this->x[pos] = c;
  }

  void setY(int c, int pos) {
    this->y[pos] = c;
  }

  string toString() {
    stringstream ss;

    ss << ShapeTwoD::toString()
       << "Area: " << getArea() << " units square" << endl << endl
       << "Vertices: " << endl;

    for (int i = 0; i < 12; i++) {
      ss << "Point [" << i+1 << "]: (" << x[i] << ", " << y[i] << ")" << endl;
    }

    findmm();

    int none = 0;
    ss << endl << "Points on perimeter:" << endl;
    for (int j = miny; j < maxy+1; j++) {
      for (int i = minx; i < maxx+1; i++) {
        if (isPointOnShape(i, j)) {
          ss << "(" << i << ", " << j << ")" << endl;
          none++;
        }
      }
    }

    if (none == 0) {
      ss << "none!" << endl;
    }

    none = 0;
    ss << endl
       << "Points within shape:" << endl;
    for (int j = miny+1; j < maxy ; j++) {
      for (int i = minx+1; i < maxx; i++) {
        if (isPointInShape(i, j)) {
          ss << "(" << i << ", " << j << ")" << endl;
          none++;
        }
      }
    }

    if (none == 0) {
      ss << "none!" << endl;
    }

    return ss.str();
  }

  //computes the area of the shape
  //coordiantes must be entered in a clockwise
  //or anti clockwise manner for it to work
  double computeArea() {
    double total = 0;
    for (int i = 0; i < 11; i++) {
      total += ((x[i] * y[i+1]) - (y[i] * x[i+1]));
    }

    total += ((x[11] * y[0]) - (y[11] * x[0]));
    total = (total/2);

    return abs(total);
  }

  bool isPointOnShape(int xv, int yv) {
    int low, high;
  	for (int i = 0; i < 12; i++) {
  		int j = i + 1;

      //to form a loop within the shape
  		if (j == 12) {
        j = 0;
      }

      //return false if it is a point in the stored coordinates
  		if (x[i] == xv && y[i] == yv) {
        return false;
      }

      //checks if the two coordiantes used to compare shares the
      //same x coordinate, if so, check for y
  		if (x[i] == x[j]) {
  			low = min(y[i], y[j]);
  			high = max(y[i], y[j]);
  			if ((xv == x[i]) && (low < yv && yv < high))
  				return true;
  		}

      //else check for x
  		else if (y[i] == y[j]) {
  			low = min(x[i], x[j]);
  			high = max(x[i], x[j]);
  			if ((yv == y[i]) && (low < xv && xv < high))
  				return true;
  		}
  	}
  	return false;
  }

  bool isPointInShape(int xv, int yv) {
    //if point is outside the blanket rectangle, return false
    if ((xv <= minx) && (xv >= maxx) && (yv <= miny) && (yv >= maxy)) {
      return false;
    }

    //if point is a stored coordinate, return false
    for (int i = 0; i < 12; i++) {
      if ((x[i] == xv) && (y[i] == yv)) {
        return false;
      }
    }

    //if point is a pointOnShape, return false
    if (isPointOnShape(xv, yv)) {
      return false;
    }

    bool isInside = false;

    for (int i = 0, j = 11; i < 12; j = i++) {
      if (((y[i] > yv) != (y[j] > yv)) && (xv < (x[j] - x[i]) * (yv - y[i]) / (y[j] - y[i]) + x[i])) {
        isInside = !isInside;
      }
    }
    return isInside;
  }
};

class Circle : public ShapeTwoD {
private:
  int x[1];
  int y[1];
  int r[1];

public:
  //accessor
  int getX() {
    return x[0];
  }

  int getY() {
    return y[0];
  }

  int getR() {
    return r[0];
  }

  //mutators
  void setX(int c, int pos) {
    this->x[pos] = c;
  }

  void setY(int c, int pos) {
    this->y[pos] = c;
  }

  void setR(int c, int pos) {
    this->r[pos] = c;
  }

  string toString() {
    stringstream ss;

    ss << ShapeTwoD::toString()
       << "Radius: " << r[0] << " units" << endl
       << "Area: " << fixed << setprecision(2) << getArea() << " units square" << endl << endl
       << "Vertices: " << endl
       << "Point [1]: (" << x[0] << ", " << y[0] << ")" << endl;

       int maxx = x[0] + r[0];
       int maxy = y[0] + r[0];
       int minx = x[0] - r[0];
       int miny = y[0] - r[0];

       int none = 0;
       ss << endl << "Points on perimeter:" << endl;
       for (int j = miny; j < maxy+1; j++) {
         for (int i = minx; i < maxx+1; i++) {
           if (isPointOnShape(i, j)) {
             ss << "(" << i << ", " << j << ")" << endl;
             none++;
           }
         }
       }

       if (none == 0) {
         ss << "none!" << endl;
       }

       ss << endl
          << "Points within shape:" << endl;
       for (int j = miny+1; j < maxy; j++) {
         for (int i = minx+1; i < maxx; i++) {
           if (isPointInShape(i, j)) {
             ss << "(" << i << ", " << j << ")" << endl;
             none++;
           }
         }
       }

       if (none == 0) {
         ss << "none!" << endl;
       }

    return ss.str();
  }

  double computeArea() {
    double total = M_PI * ((r[0]) * (r[0]));
    return total;
  }

  //checks for on shape using the center of the circle
  //and calculating to get the outer shape surrounding
  //the center
  bool isPointOnShape(int xv, int yv) {
    int dx, dy, d;
  	int xc = x[0];
  	int yc = y[0];

  	dx = (xv - xc);
  	dy = (yv - yc);
  	d = sqrt((dx * dx) + (dy * dy));

  	if (d == r[0]) {
      return true;
    }
    else {
      return false;
    }
  }

  //similar formula to the one on top,
  //but everything from the center of Circle
  //to the edge are inShape
  bool isPointInShape(int xv, int yv) {
    int dx, dy, d;
  	int xc = x[0];
  	int yc = y[0];

  	dx = (xv - xc);
  	dy = (yv - yc);
  	d = sqrt((dx * dx) + (dy * dy));

  	if (d < r[0]) {
      return true;
    }
    else {
      return false;
    }
  }
};

class Square : public ShapeTwoD {
private:
  int x[4];
  int y[4];
  int maxx = -1000;
  int maxy = -1000;
  int minx = 1000;
  int miny = 1000;

  void findmm() {
    for (int i = 0; i < 4; i++) {
      if ((x[i]) > maxx) {
        maxx = x[i];
      }
      if ((x[i]) < minx) {
        minx = x[i];
      }
      if ((y[i]) > maxy) {
        maxy = y[i];
      }
      if ((y[i]) < miny) {
        miny = y[i];
      }
    }
  }

public:
  //accessors
  int getX(int pos) {
    return x[pos];
  }

  int getY(int pos) {
    return y[pos];
  }

  //mutators
  void setX(int c, int pos) {
    this->x[pos] = c;
  }

  void setY(int c, int pos) {
    this->y[pos] = c;
  }

  string toString() {
    stringstream ss;

    ss << ShapeTwoD::toString()
       << "Area: " << getArea() << " units square" << endl << endl
       << "Vertices: " << endl << endl;

    for (int i = 0; i < 4; i++) {
      ss << "Point [" << i+1 << "]: (" << x[i] << ", " << y[i] << ")" << endl;
    }

    findmm();

    int none = 0;
    ss << endl << "Points on perimeter:" << endl;
    for (int j = miny; j < maxy+1; j++) {
      for (int i = minx; i < maxx+1; i++) {
        if (isPointOnShape(i, j)) {
          ss << "(" << i << ", " << j << ")" << endl;
          none++;
        }
      }
    }

    if (none == 0) {
      ss << "none!" << endl;
    }

    none = 0;
    ss << endl
       << "Points within shape:" << endl;
    for (int j = miny+1; j < maxy ; j++) {
      for (int i = minx+1; i < maxx; i++) {
        if (isPointInShape(i, j)) {
          ss << "(" << i << ", " << j << ")" << endl;
          none++;
        }
      }
    }

    if (none == 0) {
      ss << "none!" << endl;
    }

    return ss.str();
  }

  //computes the area of the shape
  //coordiantes must be entered in a clockwise
  //or anti clockwise manner for it to work
  double computeArea() {
    double total = 0;
    for (int i = 0; i < 3; i++) {
      total += ((x[i] * y[i+1]) - (y[i] * x[i+1]));
    }

    total += ((x[3] * y[0]) - (y[3] * x[0]));
    total = (total/2);

    return abs(total);
  }

  bool isPointOnShape(int xv, int yv) {
    //checks between edge of shape
    if (((xv > minx) && (xv < maxx)) && ((yv == miny) || (yv == maxy))) {
      return true;
    }
    else if (((yv > miny) && (yv < maxy)) && ((xv == minx) || (xv == maxx))) {
      return true;
    }
    else {
      return false;
    }
  }

  bool isPointInShape(int xv, int yv) {
    //checks between edge of shape
    if ((xv > minx) && (xv < maxx) && (yv > miny) && (yv < maxy)) {
      return true;
    }
    else {
      return false;
    }
  }
};

class Rectangle : public ShapeTwoD {
private:
  int x[4];
  int y[4];
  int maxx = -1000;
  int maxy = -1000;
  int minx = 1000;
  int miny = 1000;

  void findmm() {
    for (int i = 0; i < 4; i++) {
      if ((x[i]) > maxx) {
        maxx = x[i];
      }
      if ((x[i]) < minx) {
        minx = x[i];
      }
      if ((y[i]) > maxy) {
        maxy = y[i];
      }
      if ((y[i]) < miny) {
        miny = y[i];
      }
    }
  }

public:
  //accessors
  int getX(int pos) {
    return x[pos];
  }

  int getY(int pos) {
    return y[pos];
  }

  //mutators
  void setX(int c, int pos) {
    this->x[pos] = c;
  }

  void setY(int c, int pos) {
    this->y[pos] = c;
  }

  string toString() {
    stringstream ss;

    ss << ShapeTwoD::toString()
       << "Area: " << getArea() << " units square" << endl << endl
       << "Vertices: " << endl;

    for (int i = 0; i < 4; i++) {
      ss << "Point [" << i+1 << "]: (" << x[i] << ", " << y[i] << ")" << endl;
    }

    findmm();

    int none = 0;
    ss << endl << "Points on perimeter:" << endl;
    for (int j = miny; j < maxy+1; j++) {
      for (int i = minx; i < maxx+1; i++) {
        if (isPointOnShape(i, j)) {
          ss << "(" << i << ", " << j << ")" << endl;
          none++;
        }
      }
    }

    if (none == 0) {
      ss << "none!" << endl;
    }

    none = 0;
    ss << endl
       << "Points within shape:" << endl;
    for (int j = miny+1; j < maxy ; j++) {
      for (int i = minx+1; i < maxx; i++) {
        if (isPointInShape(i, j)) {
          ss << "(" << i << ", " << j << ")" << endl;
          none++;
        }
      }
    }

    if (none == 0) {
      ss << "none!" << endl;
    }

    return ss.str();
  }

  //computes the area of the shape
  //coordiantes must be entered in a clockwise
  //or anti clockwise manner for it to work
  double computeArea() {
    double total = 0;
    for (int i = 0; i < 3; i++) {
      total += ((x[i] * y[i+1]) - (y[i] * x[i+1]));
    }

    total += ((x[3] * y[0]) - (y[3] * x[0]));
    total = (total/2);

    return abs(total);
  }

  //checks between edge of shape
  bool isPointOnShape(int xv, int yv) {
    if (((xv > minx) && (xv < maxx)) && ((yv == miny) || (yv == maxy))) {
      return true;
    }
    else if (((yv > miny) && (yv < maxy)) && ((xv == minx) || (xv == maxx))) {
      return true;
    }
    else {
      return false;
    }
  }

  //checks between edge of shape
  bool isPointInShape(int xv, int yv) {
    if ((xv > minx) && (xv < maxx) && (yv > miny) && (yv < maxy)) {
      return true;
    }
    else {
      return false;
    }
  }
};

ShapeTwoD *records[100];
int counter = 0;
int again = 0;
int nspace = 0;
int wspace = 0;
string choice;

void displayMenu() {
  cout << endl;
  cout << "\033[0;34mStudent ID: 10193369/6098253" << endl;
  cout << "Student Name: Mohamed Shafiq Bin Roslan\033[0m" << endl;
  cout << "---------------------------------------------" << endl;
  cout << "Welcome to Assignment 2 Programme!" << endl;
  cout << endl;
  cout << "1.     Input sensor data" << endl;
  cout << "2.     Compute area for all records" << endl;
  cout << "3.     Print shapes report" << endl;
  cout << "4.     Sort shape data" << endl;
  cout << "5.     Quit" << endl;
  cout << endl;
}

//creates a new shape object that stores all the
//information needed to be displayed later
void one() {
  string shape, containsws;
  int x, y, r;
  bool ws;
  int check = 0;
  int wscheck = 0;
  Cross * crobj;
  Circle * ciobj;
  Square * sqobj;
  Rectangle * reobj;

  cout << endl;
  cout << "\033[1m\033[33m[1 -- Input sensor data]\033[0m" << endl;
  cout << endl;
  while (check == 0) {
    cout << "Please enter name of shape: ";
    cin >> shape;
    cout << endl;
    if (shape == "cross") {
      check = 1;
      crobj = new Cross;

      while (wscheck == 0) {
        cout << "Please enter special type: ";
        cin >> containsws;
        cout << endl;
        if (containsws == "WS") {
          wscheck = 1;
          wspace++;
          ws = true;
        }
        else if (containsws == "NS") {
          wscheck = 1;
          nspace++;
          ws = false;
        }
        else {
          cout << endl << "Please enter the correct information (WS/NS)" << endl;
          wscheck = 0;
        }
      }
      crobj->setName("Cross");
      crobj->setContainsWarpSpace(ws);

      cout << endl << "Please enter all coordinates in a clockwise/counter-clockwise fashion" << endl;
      for (int i = 0; i < 12; i++) {
        cout << "Please enter x-ordinate of point " << i+1 << ": ";
        cin >> x;
        cout << "Please enter y-ordinate of point " << i+1 << ": ";
        cin >> y;

        crobj->setX(x, i);
        crobj->setY(y, i);
      }
      records[counter] = crobj;
      counter++;
      crobj->setID(counter);
      cout << endl;
    }

    else if (shape == "circle") {
      check = 1;
      ciobj = new Circle;

      while (wscheck == 0) {
        cout << "Please enter special type: ";
        cin >> containsws;
        cout << endl;
        if (containsws == "WS") {
          wscheck = 1;
          wspace++;
          ws = true;
        }
        else if (containsws == "NS") {
          ws = false;
          nspace++;
          wscheck = 1;
        }
        else {
          wscheck = 0;
          cout << endl << "Please enter the correct information (WS/NS)" << endl;
        }
      }

      ciobj->setName("Circle");
      ciobj->setContainsWarpSpace(ws);

      cout << "Please enter x-ordinate of center: ";
      cin >> x;
      cout << "Please enter y-ordinate of center: ";
      cin >> y;
      cout << "Please enter radius of circle: ";
      cin >> r;
      cout << endl;

      ciobj->setX(x, 0);
      ciobj->setY(y, 0);
      ciobj->setR(r, 0);

      records[counter] = ciobj;
      counter++;
      ciobj->setID(counter);
    }

    else if (shape == "square") {
      check = 1;
      sqobj = new Square;

      while (wscheck == 0) {
        cout << "Please enter special type: ";
        cin >> containsws;
        cout << endl;
        if (containsws == "WS") {
          wscheck = 1;
          wspace++;
          ws = true;
        }
        else if (containsws == "NS") {
          wscheck = 1;
          nspace++;
          ws = false;
        }
        else {
          cout << endl << "Please enter the correct information (WS/NS)" << endl;
          wscheck = 0;
        }
      }
      sqobj->setName("Square");
      sqobj->setContainsWarpSpace(ws);

      cout << "Please enter all coordinates in a clockwise/counter-clockwise fashion" << endl;
      for (int i = 0; i < 4; i++) {
        cout << "Please enter x-ordinate of point " << i+1 << ": ";
        cin >> x;
        cout << "Please enter y-ordinate of point " << i+1 << ": ";
        cin >> y;

        sqobj->setX(x, i);
        sqobj->setY(y, i);
      }

      records[counter] = sqobj;
      counter++;
      sqobj->setID(counter);
      cout << endl;
    }

    else if (shape == "rectangle") {
      check = 1;
      reobj = new Rectangle;

      while (wscheck == 0) {
        cout << "Please enter special type: ";
        cin >> containsws;
        if (containsws == "WS") {
          wscheck = 1;
          wspace++;
          ws = true;
        }
        else if (containsws == "NS") {
          wscheck = 1;
          nspace++;
          ws = false;
        }
        else {
          cout << endl << "Please enter the correct information (WS/NS)" << endl;
          wscheck = 0;
        }
      }
      reobj->setName("Rectangle");
      reobj->setContainsWarpSpace(ws);

      cout << "Please enter all coordinates in a clockwise/counter-clockwise fashion" << endl;
      for (int i = 0; i < 4; i++) {
        cout << "Please enter x-ordinate of point " << i+1 << ": ";
        cin >> x;
        cout << "Please enter y-ordinate of point " << i+1 << ": ";
        cin >> y;

        reobj->setX(x, i);
        reobj->setY(y, i);
      }

      records[counter] = reobj;
      counter++;
      reobj->setID(counter);
      cout << endl;
    }

    else {
      cout << "Please enter the correct shape name" << endl;
      check = 0;
    }
  }
  cout << endl;
  cout << counter << " records successfully stored." << endl << endl << "Returning to main menu..." << endl;
}

//computes and sets the area variable in each shape object
void two() {
  for (int i = 0; i < counter; i++) {
    double j = records[i]->computeArea();
    records[i]->setArea(j);
  }
  cout << "Computation completed!" << endl << counter << " records successfully updated." << endl << endl << "Returning to main menu..." << endl;
}

//prints the information of the shapes
void three() {
  cout << endl;
  cout << "\033[1m\033[33m[3 -- Print shapes report]\033[0m" << endl;
  cout << endl;

  for (int i = 0; i < counter; i++) {
    cout << records[i]->toString() << endl;
    cout << "------------------------------------------------" << endl;
    cout << endl;
  }
}

//sort
void four() {
  char option;
  int fch = 0;

  cout << endl;
  cout << "\033[1m\033[33m[4 -- Sort shape data]\033[0m" << endl;

  cout << endl;
  cout << "a.     Sort by area (ascending)" << endl;
  cout << "b.     Sort by area (descending)" << endl;
  cout << "c.     Sort by special type and area" << endl;
  cout << "d.     Sort by ID" << endl;
  cout << "q.     Return to main menu" << endl;
  cout << endl;

  while (fch == 0) {
    cout << "Please select sort option: ";
    cin >> option;
    cout << endl;

    if (option == 'a') {
    fch = 1;

    cout << endl;
    cout << "\033[1m\033[33m[a --  Sort by area (ascending)]\033[0m" << endl;
    cout << endl;

    //insertion sort
    for (int i = 0; i < counter; i++) {
      for (int j = i+1; j < counter; j++) {
        if (records[i]->getArea() > records[j]->getArea()) {
          ShapeTwoD *temp = records[i];
          records[i] = records[j];
          records[j] = temp;
        }
      }
    }

      for (int i = 0; i < counter; i++) {
        cout << records[i]->toString() << endl;
        cout << "------------------------------------------------" << endl;
        cout << endl;
      }
    four();
    }

    else if (option == 'b') {
      fch = 1;

      cout << endl;
      cout << "\033[1m\033[33m[b --  Sort by area (descending)]\033[0m" << endl;
      cout << endl;

      //insertion sort
      for (int i = 0; i < counter; i++) {
        for (int j = i+1; j < counter; j++) {
          if (records[i]->getArea() < records[j]->getArea()) {
            ShapeTwoD *temp = records[i];
            records[i] = records[j];
            records[j] = temp;
			    }
		    }
	    }

      for (int i = 0; i < counter; i++) {
        cout << records[i]->toString() << endl;
        cout << "------------------------------------------------" << endl;
        cout << endl;
      }
      four();
    }

    else if (option == 'c') {
      fch = 1;
      ShapeTwoD *tempw[wspace];
      ShapeTwoD *tempn[nspace];
      int n = nspace;
      int w = wspace;

      cout << endl;
      cout << "\033[1m\033[33m[c --  Sort by special type and area]\033[0m" << endl;
      cout << endl;

      for (int i = 0; i < counter; i++) {
        for (int j = i+1; j < counter; j++) {
          if (records[i]->getArea() < records[j]->getArea()) {
            ShapeTwoD *temp = records[i];
            records[i] = records[j];
            records[j] = temp;
          }
        }
      }

      //after sorting, the items that are labeled WS/NS
      //are copied into a temp array
      for (int i = 0; i < counter; i++) {
        if (records[i]->getContainsWarpSpace()) {
          tempw[wspace-w] = records[i];
          w--;
        }
        else {
          tempn[nspace-n] = records[i];
          n--;
        }
      }

      //WS stored first followed by NS
      for (int i = 0; i < wspace; i++) {
        records[i] = tempw[i];
      }

      int k = 0;
      for (int i = wspace; i < counter; i++) {
        records[i] = tempn[k];
        k++;
      }

      for (int i = 0; i < counter; i++) {
        cout << records[i]->toString() << endl;
        cout << "------------------------------------------------" << endl;
        cout << endl;
      }
      four();
    }

    else if (option == 'd') {
      fch = 1;

      cout << endl;
      cout << "\033[1m\033[33m[d --  Sort by ID]\033[0m" << endl;
      cout << endl;

      //insertion sort
      for (int i = 0; i < counter; i++) {
        for (int j = i+1; j < counter; j++) {
          if (records[i]->getID() > records[j]->getID()) {
            ShapeTwoD *temp = records[i];
            records[i] = records[j];
            records[j] = temp;
          }
        }
      }

      for (int i = 0; i < counter; i++) {
        cout << records[i]->toString() << endl;
        cout << "------------------------------------------------" << endl;
        cout << endl;
      }
      four();
    }

    else if (option == 'q') {
      fch = 1;
      displayMenu();
    }

    else {
      cout << "Please enter the correct input" << endl;
      fch = 0;
    }
  }
}

int main() {

  displayMenu();
  while (again == 0) {
    cout << "Please enter your choice: ";
    cin >> choice;

    if (((choice == "2") || (choice == "3") || (choice == "4"))  && (counter == 0)) {
      again = 1;
      cout << endl << "\033[1m\033[31mPlease input some shapes before proceeding with other options\033[0m" << endl;
      cout << "Press ENTER to return to main menu ";
      cin.ignore();
      cin.ignore();
      displayMenu();
      again = 0;
    }

    else if (choice == "1") {
      again = 1;
      one();
      displayMenu();
      again = 0;
    }
    else if (choice == "2") {
      again = 1;
      two();
      displayMenu();
      again = 0;
    }
    else if (choice == "3") {
      again = 1;
      three();
      cout << "Press ENTER to return to main menu ";
      cin.ignore();
      cin.ignore();
      displayMenu();
      again = 0;
    }
    else if (choice == "4") {
      again = 1;
      four();
      again = 0;
    }
    else if (choice == "5") {
      again = 1;
      cout << "Goodbye!" << endl;
      exit(1);
    }
    else {
      cout << "Please enter 1 - 5" << endl;
      cout << endl;
      again = 0;
    }
  }
  return 0;
}
