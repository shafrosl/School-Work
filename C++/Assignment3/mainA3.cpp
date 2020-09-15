#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <math.h>
#include <fstream>

#include "Point2D.h"
#include "Point3D.h"
#include "Line2D.h"
#include "Line3D.h"

using namespace std;

string filter = "Point2D";
string sortby = "X-Ordinate";
string order = "Ascending";

string import;
ifstream infile;
int records = 0;
int check = 0;

Point2D pt2d;
Point3D pt3d;
Line2D ln2d;
Line3D ln3d;

vector <Point2D> pt2dv;
vector <Point3D> pt3dv;
vector <Line2D> ln2dv;
vector <Line3D> ln3dv;

vector <Point2D>::iterator p2it;
vector <Point3D>::iterator p3it;
vector <Line2D>::iterator l2it;
vector <Line3D>::iterator l3it;

bool P2Dsortbyx (Point2D p1, Point2D p2);
bool P2Dsortbyy (Point2D p1, Point2D p2);
bool P2Dsortbys (Point2D p1, Point2D p2);
bool P3Dsortbyx (Point3D p1, Point3D p2);
bool P3Dsortbyy (Point3D p1, Point3D p2);
bool P3Dsortbyz (Point3D p1, Point3D p2);
bool P3Dsortbys (Point3D p1, Point3D p2);
bool L2Dsortbyp1 (Line2D ln1, Line2D ln2);
bool L2Dsortbyp2 (Line2D ln1, Line2D ln2);
bool L2Dsortbyl (Line2D ln1, Line2D ln2);
bool L3Dsortbyp1 (Line3D ln1, Line3D ln2);
bool L3Dsortbyp2 (Line3D ln1, Line3D ln2);
bool L3Dsortbyl (Line3D ln1, Line3D ln2);

bool P2Dsortbyx (Point2D p1, Point2D p2) {
	return (p1.getX() < p2.getX());
}

bool P2Dsortbyy (Point2D p1, Point2D p2) {
	return (p1.getY() < p2.getY());
}

bool P2Dsortbys (Point2D p1, Point2D p2) {
	return (p1.getScalarValue() < p2.getScalarValue());
}

bool P3Dsortbyx (Point3D p1, Point3D p2) {
	return (p1.getX() < p2.getX());
}

bool P3Dsortbyy (Point3D p1, Point3D p2) {
	return (p1.getY() < p2.getY());
}

bool P3Dsortbyz (Point3D p1, Point3D p2) {
	return (p1.getZ() < p2.getZ());
}

bool P3Dsortbys (Point3D p1, Point3D p2) {
	return (p1.getScalarValue() < p2.getScalarValue());
}


bool L2Dsortbyp1 (Line2D ln1, Line2D ln2) {
	if (ln1.getP1().getX() == ln2.getP1().getX()) {
		return ( ln1.getP1().getY() < ln2.getP1().getY());
	}

	else {
		return (ln1.getP1().getX() < ln2.getP1().getX());
	}
}

bool L2Dsortbyp2 (Line2D ln1, Line2D ln2) {
	if (ln1.getP2().getX() == ln2.getP2().getX()) {
		return ( ln1.getP2().getY() < ln2.getP2().getY());
	}

	else {
		return (ln1.getP2().getX() < ln2.getP2().getX());
	}
}

bool L3Dsortbyp1 (Line3D ln1, Line3D ln2) {
	if (ln1.getP1().getX() == ln2.getP1().getX()) {
		return ( ln1.getP1().getY() < ln2.getP1().getY());
	}

	else {
    return (ln1.getP1().getX() < ln2.getP1().getX());
  }
}

bool L3Dsortbyp2 (Line3D ln1, Line3D ln2) {
	if (ln1.getP2().getX() == ln2.getP2().getX()) {
		return ( ln1.getP2().getY() < ln2.getP2().getY());
	}

	else {
    return (ln1.getP2().getX() < ln2.getP2().getX());
  }
}

bool L3Dsortbyl (Line3D ln1, Line3D ln2) {
	return (ln1.getScalarValue() < ln2.getScalarValue());
}

bool L2Dsortbyl (Line2D ln1, Line2D ln2) {
	return (ln1.getScalarValue() < ln2.getScalarValue());
}

ostream& P2DHeader (ostream &output) {
	output << right << setw(5) << "X";
	output << right << setw(6) << "Y";
	output << "  ";
	output << right << setw(17) << "Dist. Fr Origin" << endl;
	output << setw(45) << setfill('-') << "-" << endl;
	output << setfill(' ');
	return output;
}

ostream& P3DHeader (ostream &output) {
	output << right << setw(5) << "X";
	output << right << setw(6) << "Y";
	output << right << setw(6) << "Z";
	output << "  ";
	output << right << setw(17) << "Dist. Fr Origin" << endl;
	output << setw(50) << setfill('-') << "-" << endl;
	output << setfill(' ');
	return output;
}

ostream& L2DHeader (ostream &output) {
	output << right << setw(5) << "P1-X";
	output << "  ";
	output << right << setw(5) << "P1-Y";
	output << "  ";
	output << right << setw(5) << "P2-X";
	output << "   ";
	output << right << setw(5) << "P2-Y";
	output << right << setw(9) << "Length" << endl;
	output << setw(50) << setfill('-') << "-" << endl;
	output << setfill(' ');
	return output;
}

ostream& L3DHeader (ostream &output) {
	output << right << setw(5) << "P1-X";
	output << right << setw(6) << "P1-Y";
	output << right << setw(6) << "P1-Z";
	output << "    ";
	output << right << setw(5) << "P2-X";
	output << right << setw(6) << "P2-Y";
	output << right << setw(6) << "P2-Z";
	output << right << setw(10) << "Length" << endl;
	output << setw(60) << setfill('-') << "-" << endl;
	output << setfill(' ');
	return output;
}

void displayMenu() {
  if (check == 0) {
    cout << endl;
    cout << "\033[0;34mStudent ID: 10193369/6098253" << endl;
    cout << "Student Name: Mohamed Shafiq Bin Roslan\033[0m" << endl;
    cout << "---------------------------------------------" << endl;
    cout << "\033[1m\033[33mWelcome to the Third and Final Assignment!\033[0m" << endl;
    cout << endl;
    cout << "1.     Read in data" << endl;
    cout << "2.     Specify filtering criteria" << endl;
    cout << "3.     Specify sorting criteria" << endl;
    cout << "4.     Specify sorting order" << endl;
    cout << "5.     View data" << endl;
    cout << "6.     Store data" << endl;
    cout << "7.     Quit" << endl;
    cout << endl;
  }
  else {
    cout << endl;
    cout << "\033[0;34mStudent ID: 10193369/6098253" << endl;
    cout << "Student Name: Mohamed Shafiq Bin Roslan\033[0m" << endl;
    cout << "---------------------------------------------" << endl;
    cout << "\033[1m\033[33mWelcome to the Third and Final Assignment!\033[0m" << endl;
    cout << endl;
    cout << "1.     Read in data" << endl;
    cout << "2.     Specify filtering criteria (Current: " << filter << ")" << endl;
    cout << "3.     Specify sorting criteria (Current: " << sortby << ")" << endl;
    cout << "4.     Specify sorting order (Current: " << order << ")" << endl;
    cout << "5.     View data" << endl;
    cout << "6.     Store data" << endl;
    cout << "7.     Quit" << endl;
    cout << endl;
  }
}

void one() {
  cout << endl;
  cout << "\033[1m\033[33m[1 -- Read in data]\033[0m" << endl;
  cout << endl;

  cout << "Please enter filename: ";
  cin >> import;
  cout << endl;

  infile.open(import);

  if (!infile) {
    cout << "File not found!" << endl;
  }
  else {
    string type;

    while (!infile.eof()) {
      infile >> type;

      Point2D pt2d2;
      Point3D pt3d2;
      Line2D ln2d2;
      Line3D ln3d2;

      if (type == "Point2D,") {
        infile >> pt2d;
        p2it = pt2dv.begin();
        bool Tvalue = true;

        while (p2it != pt2dv.end()) {
          pt2d2 = *p2it;

          if (pt2d == pt2d2) {
            Tvalue = false;
          }
          p2it++;
        }

        if (Tvalue == true) {
          pt2dv.push_back(pt2d);
          records++;
        }
      }

      else if (type == "Point3D,") {
        infile >> pt3d;
        p3it = pt3dv.begin ();
        bool Tvalue = true;

        while (p3it != pt3dv.end ()) {
          pt3d2 = *p3it;

          if (pt3d == pt3d2) {
            Tvalue = false;
          }
          p3it++;
        }

        if (Tvalue == true) {
          pt3dv.push_back (pt3d);
          records++;
        }
      }

      else if (type == "Line2D,") {
        infile >> ln2d;
        l2it = ln2dv.begin ();
        bool Tvalue = true;

        while (l2it != ln2dv.end ()) {
          ln2d2 = *l2it;

          if (ln2d == ln2d2) {
            Tvalue = false;
          }
          l2it++;
        }

        if (Tvalue == true) {
          ln2dv.push_back(ln2d);
          records++;
        }
      }

      else if (type == "Line3D,") {
        infile >> ln3d;
        l3it = ln3dv.begin();
        bool Tvalue = true;

        while (l3it != ln3dv.end()) {
          ln3d2 = *l3it;

          if (ln3d == ln3d2) {
            Tvalue = false;
          }
          l3it++;
        }

        if (Tvalue == true) {
          ln3dv.push_back (ln3d);
          records++;
        }
      }
      infile.ignore ();
    }
    infile.close ();
    cout << endl;
    cout << records << " records read in successfully!" << endl;
    cout << endl;
    cout << "Returning to main menu..." << endl;
    cout << endl;
  }
}

void two() {
  char option = 'e';

  cout << endl;
  cout << "\033[1m\033[33m[2 -- Specify filtering criteria (Current: " << filter << ")]\033[0m" << endl;
  cout << endl;
  cout << "a.     Point2D Records" << endl;
  cout << "b.     Point3D Records" << endl;
  cout << "c.     Line2D  Records" << endl;
  cout << "d.     Line3D  Records" << endl;
  cout << endl;

  while (option > 'd') {
    cout << "Please enter your choice (a-d): ";
    cin >> option;
    cout << endl;
  }

  if (option == 'a') {
    filter = "Point2D";
    sortby = "X-Ordinate";
  }

  else if (option == 'b') {
    filter = "Point3D";
    sortby = "X-Ordinate";
  }

  else if (option == 'c') {
    filter = "Line2D";
    sortby = "Point 1";
  }

  else if (option == 'd') {
    filter = "Line3D";
    sortby = "Point 1";
  }

  cout << "Filter criteria successfully changed to " << filter << "!" << endl;
  cout << endl;
  cout << "Returning to main menu..." << endl;
  cout << endl;
}

void three() {
  char option;

  cout << endl;
  cout << "\033[1m\033[33m[3 -- Specify sorting criteria (Current: " << sortby << ")]\033[0m" << endl;
  cout << endl;

  if (filter == "Point2D") {
    option = 'e';

    cout << "a.     x-ordinate values" << endl;
    cout << "b.     y-ordinate values" << endl;
    cout << "c.     distance from origin values" << endl;
    cout << endl;

    while (option > 'c') {
      cout << "Please enter your option: ";
      cin >> option;
      cout << endl;
    }

    if (option == 'a') {
      sortby = "X-Ordinate";
    }

    else if (option == 'b') {
      sortby = "Y-Ordinate";
    }

    else if (option == 'c') {
      sortby = "Dist. Fr Origin";
    }
  }

  else if (filter == "Point3D") {
    option = 'e';

    cout << "a.     x-ordinate values" << endl;
    cout << "b.     y-ordinate values" << endl;
    cout << "c.     z-ordinate values" << endl;
    cout << "d.     distance from origin values" << endl;
    cout << endl;

    while (option > 'd') {
      cout << "Please enter your option: ";
      cin >> option;
      cout << endl;
    }

    if (option == 'a') {
      sortby = "X-Ordinate";
    }

    else if (option == 'b') {
      sortby = "Y-Ordinate";
    }

    else if (option == 'c') {
      sortby = "Z-Ordinate";
    }

    else if (option == 'd') {
      sortby = "Dist. Fr Origin";
    }
  }

  else if (filter == "Line2D" || filter == "Line3D") {
    option = 'e';

    cout << "a.     point 1's [x, y] values" << endl;
    cout << "b.     point 2's [x, y] values" << endl;
    cout << "c.     length values" << endl;
    cout << endl;

    while (option > 'c') {
      cout << "Please enter your option: ";
      cin >> option;
      cout << endl;
    }

    if (option == 'a') {
      sortby = "Point 1";
    }

    else if (option == 'b') {
      sortby = "Point 2";
    }

    else if (option == 'c') {
      sortby = "Length";
    }
  }

  cout << "Sorting criteria successfully changed to " << sortby << "!" << endl;
  cout << endl;
  cout << "Returning to main menu..." << endl;
  cout << endl;
}

void four() {
  char option = 'e';

  cout << endl;
  cout << "\033[1m\033[33m[4 -- Specify sorting order (Current: " << order << ")]\033[0m" << endl;
  cout << endl;
  cout << "a.     Ascending" << endl;
  cout << "b.     Descending" << endl;
  cout << endl;

  while (option > 'c') {
    cout << "Please enter your choice (a/b): ";
    cin >> option;
    cout << endl;
  }

  if (option == 'a') {
    order = "Ascending";
  }

  else if (option == 'b') {
    order = "Descending";
  }

  cout << "Sorting criteria successfully changed to " << order << "!" << endl;
  cout << endl;
  cout << "Returning to main menu..." << endl;
  cout << endl;
}

void five() {
  cout << endl;
  cout << "\033[1m\033[33m[5 -- View Data]\033[0m" << endl;
  cout << endl;

  if ((filter == "Point2D") && (sortby == "X-Ordinate") && (order == "Ascending")) {
    sort(pt2dv.begin(), pt2dv.end(), P2Dsortbyx);
    cout << P2DHeader;
    p2it = pt2dv.begin();

    while (p2it != pt2dv.end()) {
			cout << fixed << showpoint << setprecision(3);
		  cout << "[";
		  cout << right << setw(4) << (*p2it).getX();
		  cout << ", ";
		  cout << right << setw(4) << (*p2it).getY();
		  cout << "]";
		  cout << "   ";
		  cout << right << setw(4) << (*p2it).getScalarValue();
			cout << endl;
      p2it++;
    }
  }

  else if ((filter == "Point2D") && (sortby == "X-Ordinate") && (order == "Descending")) {
    sort(pt2dv.rbegin(), pt2dv.rend(), P2Dsortbyx);
    cout << P2DHeader;
    p2it = pt2dv.begin();

    while (p2it != pt2dv.end()) {
			cout << fixed << showpoint << setprecision(3);
		  cout << "[";
		  cout << right << setw(4) << (*p2it).getX();
		  cout << ", ";
		  cout << right << setw(4) << (*p2it).getY();
		  cout << "]";
		  cout << "   ";
		  cout << right << setw(4) << (*p2it).getScalarValue();
			cout << endl;
      p2it++;
    }
  }

  else if ((filter == "Point2D") && (sortby == "Y-Ordinate") && (order == "Ascending")) {
    sort(pt2dv.begin(), pt2dv.end(), P2Dsortbyy);
    cout << P2DHeader;
    p2it = pt2dv.begin();

    while (p2it != pt2dv.end()) {
			cout << fixed << showpoint << setprecision(3);
		  cout << "[";
		  cout << right << setw(4) << (*p2it).getX();
		  cout << ", ";
		  cout << right << setw(4) << (*p2it).getY();
		  cout << "]";
		  cout << "   ";
		  cout << right << setw(4) << (*p2it).getScalarValue();
			cout << endl;
      p2it++;
    }
  }

  else if ((filter == "Point2D") && (sortby == "Y-Ordinate") && (order == "Descending")) {
    sort(pt2dv.rbegin(), pt2dv.rend(), P2Dsortbyy);
    cout << P2DHeader;
    p2it = pt2dv.begin();

    while (p2it != pt2dv.end()) {
			cout << fixed << showpoint << setprecision(3);
		  cout << "[";
		  cout << right << setw(4) << (*p2it).getX();
		  cout << ", ";
		  cout << right << setw(4) << (*p2it).getY();
		  cout << "]";
		  cout << "   ";
		  cout << right << setw(4) << (*p2it).getScalarValue();
			cout << endl;
      p2it++;
    }
  }

  else if ((filter == "Point2D") && (sortby == "Dist. Fr Origin") && (order == "Ascending")) {
    sort(pt2dv.begin(), pt2dv.end(), P2Dsortbys);
    cout << P2DHeader;
    p2it = pt2dv.begin();

    while (p2it != pt2dv.end()) {
			cout << fixed << showpoint << setprecision(3);
		  cout << "[";
		  cout << right << setw(4) << (*p2it).getX();
		  cout << ", ";
		  cout << right << setw(4) << (*p2it).getY();
		  cout << "]";
		  cout << "   ";
		  cout << right << setw(4) << (*p2it).getScalarValue();
			cout << endl;
      p2it++;
    }
  }

  else if ((filter == "Point2D") && (sortby == "Dist. Fr Origin") && (order == "Descending")) {
    sort(pt2dv.rbegin(), pt2dv.rend(), P2Dsortbys);
    cout << P2DHeader;
    p2it = pt2dv.begin();

    while (p2it != pt2dv.end()) {
			cout << fixed << showpoint << setprecision(3);
		  cout << "[";
		  cout << right << setw(4) << (*p2it).getX();
		  cout << ", ";
		  cout << right << setw(4) << (*p2it).getY();
		  cout << "]";
		  cout << "   ";
		  cout << right << setw(4) << (*p2it).getScalarValue();
			cout << endl;
      p2it++;
    }
  }

  else if ((filter == "Point3D") && (sortby == "X-Ordinate") && (order == "Ascending")) {
    sort(pt3dv.begin(), pt3dv.end(), P3Dsortbyx);
    cout << P3DHeader;
    p3it = pt3dv.begin();

    while (p3it != pt3dv.end()) {
			cout << fixed << showpoint << setprecision(3);
		  cout << "[";
		  cout << right << setw(4) << (*p3it).getX();
		  cout << ", ";
		  cout << right << setw(4) << (*p3it).getY();
			cout << ", ";
			cout << right << setw(4) << (*p3it).getZ();
		  cout << "]";
		  cout << "   ";
		  cout << right << setw(4) << (*p3it).getScalarValue();
			cout << endl;
      p3it++;
    }
  }

  else if ((filter == "Point3D") && (sortby == "X-Ordinate") && (order == "Descending")) {
    sort(pt3dv.rbegin(), pt3dv.rend(), P3Dsortbyx);
    cout << P3DHeader;
    p3it = pt3dv.begin();

    while (p3it != pt3dv.end()) {
			cout << fixed << showpoint << setprecision(3);
		  cout << "[";
		  cout << right << setw(4) << (*p3it).getX();
		  cout << ", ";
		  cout << right << setw(4) << (*p3it).getY();
			cout << ", ";
			cout << right << setw(4) << (*p3it).getZ();
		  cout << "]";
		  cout << "   ";
		  cout << right << setw(4) << (*p3it).getScalarValue();
			cout << endl;
      p3it++;
    }
  }

  else if ((filter == "Point3D") && (sortby == "Y-Ordinate") && (order == "Ascending")) {
    sort(pt3dv.begin(), pt3dv.end(), P3Dsortbyy);
    cout << P3DHeader;
    p3it = pt3dv.begin();

    while (p3it != pt3dv.end()) {
			cout << fixed << showpoint << setprecision(3);
		  cout << "[";
		  cout << right << setw(4) << (*p3it).getX();
		  cout << ", ";
		  cout << right << setw(4) << (*p3it).getY();
			cout << ", ";
			cout << right << setw(4) << (*p3it).getZ();
		  cout << "]";
		  cout << "   ";
		  cout << right << setw(4) << (*p3it).getScalarValue();
			cout << endl;
      p3it++;
    }
  }

  else if ((filter == "Point3D") && (sortby == "Y-Ordinate") && (order == "Descending")) {
    sort(pt3dv.rbegin(), pt3dv.rend(), P3Dsortbyy);
    cout << P3DHeader;
    p3it = pt3dv.begin();

    while (p3it != pt3dv.end()) {
			cout << fixed << showpoint << setprecision(3);
		  cout << "[";
		  cout << right << setw(4) << (*p3it).getX();
		  cout << ", ";
		  cout << right << setw(4) << (*p3it).getY();
			cout << ", ";
			cout << right << setw(4) << (*p3it).getZ();
		  cout << "]";
		  cout << "   ";
		  cout << right << setw(4) << (*p3it).getScalarValue();
			cout << endl;
      p3it++;
    }
  }
  else if ((filter == "Point3D") && (sortby == "Z-Ordinate") && (order == "Ascending")) {
    sort(pt3dv.begin(), pt3dv.end(), P3Dsortbyz);
    cout << P3DHeader;
    p3it = pt3dv.begin();

    while (p3it != pt3dv.end()) {
			cout << fixed << showpoint << setprecision(3);
		  cout << "[";
		  cout << right << setw(4) << (*p3it).getX();
		  cout << ", ";
		  cout << right << setw(4) << (*p3it).getY();
			cout << ", ";
			cout << right << setw(4) << (*p3it).getZ();
		  cout << "]";
		  cout << "   ";
		  cout << right << setw(4) << (*p3it).getScalarValue();
			cout << endl;
      p3it++;
    }
  }

  else if ((filter == "Point3D") && (sortby == "Z-Ordinate") && (order == "Descending")) {
    sort(pt3dv.rbegin(), pt3dv.rend(), P3Dsortbyz);
    cout << P3DHeader;
    p3it = pt3dv.begin();

    while (p3it != pt3dv.end()) {
			cout << fixed << showpoint << setprecision(3);
		  cout << "[";
		  cout << right << setw(4) << (*p3it).getX();
		  cout << ", ";
		  cout << right << setw(4) << (*p3it).getY();
			cout << ", ";
			cout << right << setw(4) << (*p3it).getZ();
		  cout << "]";
		  cout << "   ";
		  cout << right << setw(4) << (*p3it).getScalarValue();
			cout << endl;
      p3it++;
    }
  }

  else if ((filter == "Point3D") && (sortby == "Dist. Fr Origin") && (order == "Ascending")) {
    sort(pt3dv.begin(), pt3dv.end(), P3Dsortbys);
    cout << P3DHeader;
    p3it = pt3dv.begin();

    while (p3it != pt3dv.end()) {
			cout << fixed << showpoint << setprecision(3);
		  cout << "[";
		  cout << right << setw(4) << (*p3it).getX();
		  cout << ", ";
		  cout << right << setw(4) << (*p3it).getY();
			cout << ", ";
			cout << right << setw(4) << (*p3it).getZ();
		  cout << "]";
		  cout << "   ";
		  cout << right << setw(4) << (*p3it).getScalarValue();
			cout << endl;
      p3it++;
    }
  }

  else if ((filter == "Point3D") && (sortby == "Dist. Fr Origin") && (order == "Descending")) {
    sort(pt3dv.rbegin(), pt3dv.rend(), P3Dsortbys);
    cout << P3DHeader;
    p3it = pt3dv.begin();

    while (p3it != pt3dv.end()) {
			cout << fixed << showpoint << setprecision(3);
		  cout << "[";
		  cout << right << setw(4) << (*p3it).getX();
		  cout << ", ";
		  cout << right << setw(4) << (*p3it).getY();
			cout << ", ";
			cout << right << setw(4) << (*p3it).getZ();
		  cout << "]";
		  cout << "   ";
		  cout << right << setw(4) << (*p3it).getScalarValue();
			cout << endl;
      p3it++;
    }
  }

  else if ((filter == "Line2D") && (sortby == "Point 1") && (order == "Ascending")) {
    sort(ln2dv.begin(), ln2dv.end(), L2Dsortbyp1);
    cout << L2DHeader;
    l2it = ln2dv.begin();

    while (l2it != ln2dv.end()) {
			cout << fixed << showpoint << setprecision(3);
		  cout << "[";
		  cout << right << setw(4) << (*l2it).getP1().getX();
		  cout << ", ";
		  cout << right << setw(4) << (*l2it).getP1().getY();
		  cout << "]";
		  cout << "   ";
		  cout << "[";
		  cout << right << setw(4) << (*l2it).getP2().getX();
		  cout << ", ";
		  cout << right << setw(4) << (*l2it).getP2().getY();
		  cout << "]";
		  cout << "   ";
		  cout << left << setw(4) << (*l2it).getScalarValue();
			cout << endl;
      l2it++;
    }
  }

  else if ((filter == "Line2D") && (sortby == "Point 1") && (order == "Descending")) {
    sort(ln2dv.rbegin(), ln2dv.rend(), L2Dsortbyp1);
    cout << L2DHeader;
    l2it = ln2dv.begin();

    while (l2it != ln2dv.end()) {
			cout << fixed << showpoint << setprecision(3);
		  cout << "[";
		  cout << right << setw(4) << (*l2it).getP1().getX();
		  cout << ", ";
		  cout << right << setw(4) << (*l2it).getP1().getY();
		  cout << "]";
		  cout << "   ";
		  cout << "[";
		  cout << right << setw(4) << (*l2it).getP2().getX();
		  cout << ", ";
		  cout << right << setw(4) << (*l2it).getP2().getY();
		  cout << "]";
		  cout << "   ";
		  cout << left << setw(4) << (*l2it).getScalarValue();
			cout << endl;
      l2it++;
    }
  }

  else if ((filter == "Line2D") && (sortby == "Point 2") && (order == "Ascending")) {
    sort(ln2dv.begin(), ln2dv.end(), L2Dsortbyp2);
    cout << L2DHeader;
    l2it = ln2dv.begin();

    while (l2it != ln2dv.end()) {
			cout << fixed << showpoint << setprecision(3);
		  cout << "[";
		  cout << right << setw(4) << (*l2it).getP1().getX();
		  cout << ", ";
		  cout << right << setw(4) << (*l2it).getP1().getY();
		  cout << "]";
		  cout << "   ";
		  cout << "[";
		  cout << right << setw(4) << (*l2it).getP2().getX();
		  cout << ", ";
		  cout << right << setw(4) << (*l2it).getP2().getY();
		  cout << "]";
		  cout << "   ";
		  cout << left << setw(4) << (*l2it).getScalarValue();
			cout << endl;
      l2it++;
    }
  }

  else if ((filter == "Line2D") && (sortby == "Point 2") && (order == "Descending")) {
    sort(ln2dv.rbegin(), ln2dv.rend(), L2Dsortbyp2);
    cout << L2DHeader;
    l2it = ln2dv.begin();

    while (l2it != ln2dv.end()) {
			cout << fixed << showpoint << setprecision(3);
		  cout << "[";
		  cout << right << setw(4) << (*l2it).getP1().getX();
		  cout << ", ";
		  cout << right << setw(4) << (*l2it).getP1().getY();
		  cout << "]";
		  cout << "   ";
		  cout << "[";
		  cout << right << setw(4) << (*l2it).getP2().getX();
		  cout << ", ";
		  cout << right << setw(4) << (*l2it).getP2().getY();
		  cout << "]";
		  cout << "   ";
		  cout << left << setw(4) << (*l2it).getScalarValue();
			cout << endl;
      l2it++;
    }
  }

  else if ((filter == "Line2D") && (sortby == "Length") && (order == "Ascending")) {
    sort(ln2dv.begin(), ln2dv.end(), L2Dsortbyl);
    cout << L2DHeader;
    l2it = ln2dv.begin();

    while (l2it != ln2dv.end()) {
			cout << fixed << showpoint << setprecision(3);
		  cout << "[";
		  cout << right << setw(4) << (*l2it).getP1().getX();
		  cout << ", ";
		  cout << right << setw(4) << (*l2it).getP1().getY();
		  cout << "]";
		  cout << "   ";
		  cout << "[";
		  cout << right << setw(4) << (*l2it).getP2().getX();
		  cout << ", ";
		  cout << right << setw(4) << (*l2it).getP2().getY();
		  cout << "]";
		  cout << "   ";
		  cout << left << setw(4) << (*l2it).getScalarValue();
			cout << endl;
      l2it++;
    }
  }

  else if ((filter == "Line2D") && (sortby == "Length") && (order == "Descending")) {
    sort(ln2dv.rbegin(), ln2dv.rend(), L2Dsortbyl);
    cout << L2DHeader;
    l2it = ln2dv.begin();

    while (l2it != ln2dv.end()) {
			cout << fixed << showpoint << setprecision(3);
		  cout << "[";
		  cout << right << setw(4) << (*l2it).getP1().getX();
		  cout << ", ";
		  cout << right << setw(4) << (*l2it).getP1().getY();
		  cout << "]";
		  cout << "   ";
		  cout << "[";
		  cout << right << setw(4) << (*l2it).getP2().getX();
		  cout << ", ";
		  cout << right << setw(4) << (*l2it).getP2().getY();
		  cout << "]";
		  cout << "   ";
		  cout << left << setw(4) << (*l2it).getScalarValue();
			cout << endl;
      l2it++;
    }
  }

  else if ((filter == "Line3D") && (sortby == "Point 1") && (order == "Ascending")) {
    sort(ln3dv.begin(), ln3dv.end(), L3Dsortbyp1);
    cout << L3DHeader;
    l3it = ln3dv.begin();

    while (l3it != ln3dv.end()) {
			cout << fixed << showpoint << setprecision(3);
		  cout << "[";
		  cout << right << setw(4) << (*l3it).getP1().getX();
		  cout << ", ";
		  cout << right << setw(4) << (*l3it).getP1().getY();
		  cout << ", ";
		  cout << right << setw(4) << (*l3it).getP1().getZ();
		  cout << "]";
		  cout << "   ";
		  cout << "[";
		  cout << right << setw(4) << (*l3it).getP2().getX();
		  cout << ", ";
		  cout << right << setw(4) << (*l3it).getP2().getY();
		  cout << ", ";
		  cout << right << setw(4) << (*l3it).getP2().getZ();
		  cout << "]";
		  cout << "   ";
		  cout << left << setw(4) << (*l3it).getScalarValue();
			cout << endl;
      l3it++;
    }
  }

  else if ((filter == "Line3D") && (sortby == "Point 1") && (order == "Descending")) {
    sort(ln3dv.rbegin(), ln3dv.rend(), L3Dsortbyp1);
    cout << L3DHeader;
    l3it = ln3dv.begin();

    while (l3it != ln3dv.end()) {
			cout << fixed << showpoint << setprecision(3);
		  cout << "[";
		  cout << right << setw(4) << (*l3it).getP1().getX();
		  cout << ", ";
		  cout << right << setw(4) << (*l3it).getP1().getY();
		  cout << ", ";
		  cout << right << setw(4) << (*l3it).getP1().getZ();
		  cout << "]";
		  cout << "   ";
		  cout << "[";
		  cout << right << setw(4) << (*l3it).getP2().getX();
		  cout << ", ";
		  cout << right << setw(4) << (*l3it).getP2().getY();
		  cout << ", ";
		  cout << right << setw(4) << (*l3it).getP2().getZ();
		  cout << "]";
		  cout << "   ";
		  cout << left << setw(4) << (*l3it).getScalarValue();
			cout << endl;
      l3it++;
    }
  }

  else if ((filter == "Line3D") && (sortby == "Point 2") && (order == "Ascending")) {
    sort(ln3dv.begin(), ln3dv.end(), L3Dsortbyp2);
    cout << L3DHeader;
    l3it = ln3dv.begin();

    while (l3it != ln3dv.end()) {
			cout << fixed << showpoint << setprecision(3);
		  cout << "[";
		  cout << right << setw(4) << (*l3it).getP1().getX();
		  cout << ", ";
		  cout << right << setw(4) << (*l3it).getP1().getY();
		  cout << ", ";
		  cout << right << setw(4) << (*l3it).getP1().getZ();
		  cout << "]";
		  cout << "   ";
		  cout << "[";
		  cout << right << setw(4) << (*l3it).getP2().getX();
		  cout << ", ";
		  cout << right << setw(4) << (*l3it).getP2().getY();
		  cout << ", ";
		  cout << right << setw(4) << (*l3it).getP2().getZ();
		  cout << "]";
		  cout << "   ";
		  cout << left << setw(4) << (*l3it).getScalarValue();
			cout << endl;
      l3it++;
    }
  }

  else if ((filter == "Line3D") && (sortby == "Point 2") && (order == "Descending")) {
    sort(ln3dv.rbegin(), ln3dv.rend(), L3Dsortbyp2);
    cout << L3DHeader;
    l3it = ln3dv.begin();

    while (l3it != ln3dv.end()) {
			cout << fixed << showpoint << setprecision(3);
		  cout << "[";
		  cout << right << setw(4) << (*l3it).getP1().getX();
		  cout << ", ";
		  cout << right << setw(4) << (*l3it).getP1().getY();
		  cout << ", ";
		  cout << right << setw(4) << (*l3it).getP1().getZ();
		  cout << "]";
		  cout << "   ";
		  cout << "[";
		  cout << right << setw(4) << (*l3it).getP2().getX();
		  cout << ", ";
		  cout << right << setw(4) << (*l3it).getP2().getY();
		  cout << ", ";
		  cout << right << setw(4) << (*l3it).getP2().getZ();
		  cout << "]";
		  cout << "   ";
		  cout << left << setw(4) << (*l3it).getScalarValue();
			cout << endl;
      l3it++;
    }
  }

  else if ((filter == "Line3D") && (sortby == "Length") && (order == "Ascending")) {
    sort(ln3dv.begin(), ln3dv.end(), L3Dsortbyl);
    cout << L3DHeader;
    l3it = ln3dv.begin();

    while (l3it != ln3dv.end()) {
			cout << fixed << showpoint << setprecision(3);
		  cout << "[";
		  cout << right << setw(4) << (*l3it).getP1().getX();
		  cout << ", ";
		  cout << right << setw(4) << (*l3it).getP1().getY();
		  cout << ", ";
		  cout << right << setw(4) << (*l3it).getP1().getZ();
		  cout << "]";
		  cout << "   ";
		  cout << "[";
		  cout << right << setw(4) << (*l3it).getP2().getX();
		  cout << ", ";
		  cout << right << setw(4) << (*l3it).getP2().getY();
		  cout << ", ";
		  cout << right << setw(4) << (*l3it).getP2().getZ();
		  cout << "]";
		  cout << "   ";
		  cout << left << setw(4) << (*l3it).getScalarValue();
			cout << endl;
      l3it++;
    }
  }

  else if ((filter == "Line3D") && (sortby == "Length") && (order == "Descending")) {
    sort(ln3dv.rbegin(), ln3dv.rend(), L3Dsortbyl);
    cout << L3DHeader;
    l3it = ln3dv.begin();

    while (l3it != ln3dv.end()) {
			cout << fixed << showpoint << setprecision(3);
		  cout << "[";
		  cout << right << setw(4) << (*l3it).getP1().getX();
		  cout << ", ";
		  cout << right << setw(4) << (*l3it).getP1().getY();
		  cout << ", ";
		  cout << right << setw(4) << (*l3it).getP1().getZ();
		  cout << "]";
		  cout << "   ";
		  cout << "[";
		  cout << right << setw(4) << (*l3it).getP2().getX();
		  cout << ", ";
		  cout << right << setw(4) << (*l3it).getP2().getY();
		  cout << ", ";
		  cout << right << setw(4) << (*l3it).getP2().getZ();
		  cout << "]";
		  cout << "   ";
		  cout << left << setw(4) << (*l3it).getScalarValue();
			cout << endl;
      l3it++;
    }
  }
}

void six() {
  string print;
  ofstream outfile;
  int records = 0;

  cout << endl;
  cout << "\033[1m\033[33m[6 -- Store Data]\033[0m" << endl;
  cout << endl;

  cout << "Please enter filename (with extension): ";
  cin >> print;
  cout << endl;
  outfile.open(print);

  if (!outfile) {
    cout << "Storing of data failed!" << endl;
    cout << "Returning to main menu..." << endl;
    cout << endl;
    displayMenu();
  }

	if ((filter == "Point2D") && (sortby == "X-Ordinate") && (order == "Ascending")) {
	  sort(pt2dv.begin(), pt2dv.end(), P2Dsortbyx);
	  outfile << P2DHeader;
	  p2it = pt2dv.begin();

	  while (p2it != pt2dv.end()) {
	    outfile << fixed << showpoint << setprecision(3);
	    outfile << "[";
	    outfile << right << setw(4) << (*p2it).getX();
	    outfile << ", ";
	    outfile << right << setw(4) << (*p2it).getY();
	    outfile << "]";
	    outfile << "   ";
	    outfile << right << setw(4) << (*p2it).getScalarValue();
	    outfile << endl;
	    p2it++;
	    records++;
	  }
	}

	else if ((filter == "Point2D") && (sortby == "X-Ordinate") && (order == "Descending")) {
	  sort(pt2dv.rbegin(), pt2dv.rend(), P2Dsortbyx);
	  outfile << P2DHeader;
	  p2it = pt2dv.begin();

	  while (p2it != pt2dv.end()) {
	    outfile << fixed << showpoint << setprecision(3);
	    outfile << "[";
	    outfile << right << setw(4) << (*p2it).getX();
	    outfile << ", ";
	    outfile << right << setw(4) << (*p2it).getY();
	    outfile << "]";
	    outfile << "   ";
	    outfile << right << setw(4) << (*p2it).getScalarValue();
	    outfile << endl;
	    p2it++;
	    records++;
	  }
	}

	else if ((filter == "Point2D") && (sortby == "Y-Ordinate") && (order == "Ascending")) {
	  sort(pt2dv.begin(), pt2dv.end(), P2Dsortbyy);
	  outfile << P2DHeader;
	  p2it = pt2dv.begin();

	  while (p2it != pt2dv.end()) {
	    outfile << fixed << showpoint << setprecision(3);
	    outfile << "[";
	    outfile << right << setw(4) << (*p2it).getX();
	    outfile << ", ";
	    outfile << right << setw(4) << (*p2it).getY();
	    outfile << "]";
	    outfile << "   ";
	    outfile << right << setw(4) << (*p2it).getScalarValue();
	    outfile << endl;
	    p2it++;
	    records++;
	  }
	}

	else if ((filter == "Point2D") && (sortby == "Y-Ordinate") && (order == "Descending")) {
	  sort(pt2dv.rbegin(), pt2dv.rend(), P2Dsortbyy);
	  outfile << P2DHeader;
	  p2it = pt2dv.begin();

	  while (p2it != pt2dv.end()) {
	    outfile << fixed << showpoint << setprecision(3);
	    outfile << "[";
	    outfile << right << setw(4) << (*p2it).getX();
	    outfile << ", ";
	    outfile << right << setw(4) << (*p2it).getY();
	    outfile << "]";
	    outfile << "   ";
	    outfile << right << setw(4) << (*p2it).getScalarValue();
	    outfile << endl;
	    p2it++;
	    records++;
	  }
	}

	else if ((filter == "Point2D") && (sortby == "Dist. Fr Origin") && (order == "Ascending")) {
	  sort(pt2dv.begin(), pt2dv.end(), P2Dsortbys);
	  outfile << P2DHeader;
	  p2it = pt2dv.begin();

	  while (p2it != pt2dv.end()) {
	    outfile << fixed << showpoint << setprecision(3);
	    outfile << "[";
	    outfile << right << setw(4) << (*p2it).getX();
	    outfile << ", ";
	    outfile << right << setw(4) << (*p2it).getY();
	    outfile << "]";
	    outfile << "   ";
	    outfile << right << setw(4) << (*p2it).getScalarValue();
	    outfile << endl;
	    p2it++;
	    records++;
	  }
	}

	else if ((filter == "Point2D") && (sortby == "Dist. Fr Origin") && (order == "Descending")) {
	  sort(pt2dv.rbegin(), pt2dv.rend(), P2Dsortbys);
	  outfile << P2DHeader;
	  p2it = pt2dv.begin();

	  while (p2it != pt2dv.end()) {
	    outfile << fixed << showpoint << setprecision(3);
	    outfile << "[";
	    outfile << right << setw(4) << (*p2it).getX();
	    outfile << ", ";
	    outfile << right << setw(4) << (*p2it).getY();
	    outfile << "]";
	    outfile << "   ";
	    outfile << right << setw(4) << (*p2it).getScalarValue();
	    outfile << endl;
	    p2it++;
	    records++;
	  }
	}

	else if ((filter == "Point3D") && (sortby == "X-Ordinate") && (order == "Ascending")) {
	  sort(pt3dv.begin(), pt3dv.end(), P3Dsortbyx);
	  outfile << P3DHeader;
	  p3it = pt3dv.begin();

	  while (p3it != pt3dv.end()) {
	    outfile << fixed << showpoint << setprecision(3);
	    outfile << "[";
	    outfile << right << setw(4) << (*p3it).getX();
	    outfile << ", ";
	    outfile << right << setw(4) << (*p3it).getY();
	    outfile << ", ";
	    outfile << right << setw(4) << (*p3it).getZ();
	    outfile << "]";
	    outfile << "   ";
	    outfile << right << setw(4) << (*p3it).getScalarValue();
	    outfile << endl;
	    p3it++;
	    records++;
	  }
	}

	else if ((filter == "Point3D") && (sortby == "X-Ordinate") && (order == "Descending")) {
	  sort(pt3dv.rbegin(), pt3dv.rend(), P3Dsortbyx);
	  outfile << P3DHeader;
	  p3it = pt3dv.begin();

	  while (p3it != pt3dv.end()) {
	    outfile << fixed << showpoint << setprecision(3);
	    outfile << "[";
	    outfile << right << setw(4) << (*p3it).getX();
	    outfile << ", ";
	    outfile << right << setw(4) << (*p3it).getY();
	    outfile << ", ";
	    outfile << right << setw(4) << (*p3it).getZ();
	    outfile << "]";
	    outfile << "   ";
	    outfile << right << setw(4) << (*p3it).getScalarValue();
	    outfile << endl;
	    p3it++;
	    records++;
	  }
	}

	else if ((filter == "Point3D") && (sortby == "Y-Ordinate") && (order == "Ascending")) {
	  sort(pt3dv.begin(), pt3dv.end(), P3Dsortbyy);
	  outfile << P3DHeader;
	  p3it = pt3dv.begin();

	  while (p3it != pt3dv.end()) {
	    outfile << fixed << showpoint << setprecision(3);
	    outfile << "[";
	    outfile << right << setw(4) << (*p3it).getX();
	    outfile << ", ";
	    outfile << right << setw(4) << (*p3it).getY();
	    outfile << ", ";
	    outfile << right << setw(4) << (*p3it).getZ();
	    outfile << "]";
	    outfile << "   ";
	    outfile << right << setw(4) << (*p3it).getScalarValue();
	    outfile << endl;
	    p3it++;
	    records++;
	  }
	}

	else if ((filter == "Point3D") && (sortby == "Y-Ordinate") && (order == "Descending")) {
	  sort(pt3dv.rbegin(), pt3dv.rend(), P3Dsortbyy);
	  outfile << P3DHeader;
	  p3it = pt3dv.begin();

	  while (p3it != pt3dv.end()) {
	    outfile << fixed << showpoint << setprecision(3);
	    outfile << "[";
	    outfile << right << setw(4) << (*p3it).getX();
	    outfile << ", ";
	    outfile << right << setw(4) << (*p3it).getY();
	    outfile << ", ";
	    outfile << right << setw(4) << (*p3it).getZ();
	    outfile << "]";
	    outfile << "   ";
	    outfile << right << setw(4) << (*p3it).getScalarValue();
	    outfile << endl;
	    p3it++;
	    records++;
	  }
	}
	else if ((filter == "Point3D") && (sortby == "Z-Ordinate") && (order == "Ascending")) {
	  sort(pt3dv.begin(), pt3dv.end(), P3Dsortbyz);
	  outfile << P3DHeader;
	  p3it = pt3dv.begin();

	  while (p3it != pt3dv.end()) {
	    outfile << fixed << showpoint << setprecision(3);
	    outfile << "[";
	    outfile << right << setw(4) << (*p3it).getX();
	    outfile << ", ";
	    outfile << right << setw(4) << (*p3it).getY();
	    outfile << ", ";
	    outfile << right << setw(4) << (*p3it).getZ();
	    outfile << "]";
	    outfile << "   ";
	    outfile << right << setw(4) << (*p3it).getScalarValue();
	    outfile << endl;
	    p3it++;
	    records++;
	  }
	}

	else if ((filter == "Point3D") && (sortby == "Z-Ordinate") && (order == "Descending")) {
	  sort(pt3dv.rbegin(), pt3dv.rend(), P3Dsortbyz);
	  outfile << P3DHeader;
	  p3it = pt3dv.begin();

	  while (p3it != pt3dv.end()) {
	    outfile << fixed << showpoint << setprecision(3);
	    outfile << "[";
	    outfile << right << setw(4) << (*p3it).getX();
	    outfile << ", ";
	    outfile << right << setw(4) << (*p3it).getY();
	    outfile << ", ";
	    outfile << right << setw(4) << (*p3it).getZ();
	    outfile << "]";
	    outfile << "   ";
	    outfile << right << setw(4) << (*p3it).getScalarValue();
	    outfile << endl;
	    p3it++;
	    records++;
	  }
	}

	else if ((filter == "Point3D") && (sortby == "Dist. Fr Origin") && (order == "Ascending")) {
	  sort(pt3dv.begin(), pt3dv.end(), P3Dsortbys);
	  outfile << P3DHeader;
	  p3it = pt3dv.begin();

	  while (p3it != pt3dv.end()) {
	    outfile << fixed << showpoint << setprecision(3);
	    outfile << "[";
	    outfile << right << setw(4) << (*p3it).getX();
	    outfile << ", ";
	    outfile << right << setw(4) << (*p3it).getY();
	    outfile << ", ";
	    outfile << right << setw(4) << (*p3it).getZ();
	    outfile << "]";
	    outfile << "   ";
	    outfile << right << setw(4) << (*p3it).getScalarValue();
	    outfile << endl;
	    p3it++;
	    records++;
	  }
	}

	else if ((filter == "Point3D") && (sortby == "Dist. Fr Origin") && (order == "Descending")) {
	  sort(pt3dv.rbegin(), pt3dv.rend(), P3Dsortbys);
	  outfile << P3DHeader;
	  p3it = pt3dv.begin();

	  while (p3it != pt3dv.end()) {
	    outfile << fixed << showpoint << setprecision(3);
	    outfile << "[";
	    outfile << right << setw(4) << (*p3it).getX();
	    outfile << ", ";
	    outfile << right << setw(4) << (*p3it).getY();
	    outfile << ", ";
	    outfile << right << setw(4) << (*p3it).getZ();
	    outfile << "]";
	    outfile << "   ";
	    outfile << right << setw(4) << (*p3it).getScalarValue();
	    outfile << endl;
	    p3it++;
	    records++;
	  }
	}

	else if ((filter == "Line2D") && (sortby == "Point 1") && (order == "Ascending")) {
	  sort(ln2dv.begin(), ln2dv.end(), L2Dsortbyp1);
	  outfile << L2DHeader;
	  l2it = ln2dv.begin();

	  while (l2it != ln2dv.end()) {
	    outfile << fixed << showpoint << setprecision(3);
	    outfile << "[";
	    outfile << right << setw(4) << (*l2it).getP1().getX();
	    outfile << ", ";
	    outfile << right << setw(4) << (*l2it).getP1().getY();
	    outfile << "]";
	    outfile << "   ";
	    outfile << "[";
	    outfile << right << setw(4) << (*l2it).getP2().getX();
	    outfile << ", ";
	    outfile << right << setw(4) << (*l2it).getP2().getY();
	    outfile << "]";
	    outfile << "   ";
	    outfile << left << setw(4) << (*l2it).getScalarValue();
	    outfile << endl;
	    l2it++;
	    records++;
	  }
	}

	else if ((filter == "Line2D") && (sortby == "Point 1") && (order == "Descending")) {
	  sort(ln2dv.rbegin(), ln2dv.rend(), L2Dsortbyp1);
	  outfile << L2DHeader;
	  l2it = ln2dv.begin();

	  while (l2it != ln2dv.end()) {
	    outfile << fixed << showpoint << setprecision(3);
	    outfile << "[";
	    outfile << right << setw(4) << (*l2it).getP1().getX();
	    outfile << ", ";
	    outfile << right << setw(4) << (*l2it).getP1().getY();
	    outfile << "]";
	    outfile << "   ";
	    outfile << "[";
	    outfile << right << setw(4) << (*l2it).getP2().getX();
	    outfile << ", ";
	    outfile << right << setw(4) << (*l2it).getP2().getY();
	    outfile << "]";
	    outfile << "   ";
	    outfile << left << setw(4) << (*l2it).getScalarValue();
	    outfile << endl;
	    l2it++;
	    records++;
	  }
	}

	else if ((filter == "Line2D") && (sortby == "Point 2") && (order == "Ascending")) {
	  sort(ln2dv.begin(), ln2dv.end(), L2Dsortbyp2);
	  outfile << L2DHeader;
	  l2it = ln2dv.begin();

	  while (l2it != ln2dv.end()) {
	    outfile << fixed << showpoint << setprecision(3);
	    outfile << "[";
	    outfile << right << setw(4) << (*l2it).getP1().getX();
	    outfile << ", ";
	    outfile << right << setw(4) << (*l2it).getP1().getY();
	    outfile << "]";
	    outfile << "   ";
	    outfile << "[";
	    outfile << right << setw(4) << (*l2it).getP2().getX();
	    outfile << ", ";
	    outfile << right << setw(4) << (*l2it).getP2().getY();
	    outfile << "]";
	    outfile << "   ";
	    outfile << left << setw(4) << (*l2it).getScalarValue();
	    outfile << endl;
	    l2it++;
	    records++;
	  }
	}

	else if ((filter == "Line2D") && (sortby == "Point 2") && (order == "Descending")) {
	  sort(ln2dv.rbegin(), ln2dv.rend(), L2Dsortbyp2);
	  outfile << L2DHeader;
	  l2it = ln2dv.begin();

	  while (l2it != ln2dv.end()) {
	    outfile << fixed << showpoint << setprecision(3);
	    outfile << "[";
	    outfile << right << setw(4) << (*l2it).getP1().getX();
	    outfile << ", ";
	    outfile << right << setw(4) << (*l2it).getP1().getY();
	    outfile << "]";
	    outfile << "   ";
	    outfile << "[";
	    outfile << right << setw(4) << (*l2it).getP2().getX();
	    outfile << ", ";
	    outfile << right << setw(4) << (*l2it).getP2().getY();
	    outfile << "]";
	    outfile << "   ";
	    outfile << left << setw(4) << (*l2it).getScalarValue();
	    outfile << endl;
	    l2it++;
	    records++;
	  }
	}

	else if ((filter == "Line2D") && (sortby == "Length") && (order == "Ascending")) {
	  sort(ln2dv.begin(), ln2dv.end(), L2Dsortbyl);
	  outfile << L2DHeader;
	  l2it = ln2dv.begin();

	  while (l2it != ln2dv.end()) {
	    outfile << fixed << showpoint << setprecision(3);
	    outfile << "[";
	    outfile << right << setw(4) << (*l2it).getP1().getX();
	    outfile << ", ";
	    outfile << right << setw(4) << (*l2it).getP1().getY();
	    outfile << "]";
	    outfile << "   ";
	    outfile << "[";
	    outfile << right << setw(4) << (*l2it).getP2().getX();
	    outfile << ", ";
	    outfile << right << setw(4) << (*l2it).getP2().getY();
	    outfile << "]";
	    outfile << "   ";
	    outfile << left << setw(4) << (*l2it).getScalarValue();
	    outfile << endl;
	    l2it++;
	    records++;
	  }
	}

	else if ((filter == "Line2D") && (sortby == "Length") && (order == "Descending")) {
	  sort(ln2dv.rbegin(), ln2dv.rend(), L2Dsortbyl);
	  outfile << L2DHeader;
	  l2it = ln2dv.begin();

	  while (l2it != ln2dv.end()) {
	    outfile << fixed << showpoint << setprecision(3);
	    outfile << "[";
	    outfile << right << setw(4) << (*l2it).getP1().getX();
	    outfile << ", ";
	    outfile << right << setw(4) << (*l2it).getP1().getY();
	    outfile << "]";
	    outfile << "   ";
	    outfile << "[";
	    outfile << right << setw(4) << (*l2it).getP2().getX();
	    outfile << ", ";
	    outfile << right << setw(4) << (*l2it).getP2().getY();
	    outfile << "]";
	    outfile << "   ";
	    outfile << left << setw(4) << (*l2it).getScalarValue();
	    outfile << endl;
	    l2it++;
	    records++;
	  }
	}

	else if ((filter == "Line3D") && (sortby == "Point 1") && (order == "Ascending")) {
	  sort(ln3dv.begin(), ln3dv.end(), L3Dsortbyp1);
	  outfile << L3DHeader;
	  l3it = ln3dv.begin();

	  while (l3it != ln3dv.end()) {
	    outfile << fixed << showpoint << setprecision(3);
	    outfile << "[";
	    outfile << right << setw(4) << (*l3it).getP1().getX();
	    outfile << ", ";
	    outfile << right << setw(4) << (*l3it).getP1().getY();
	    outfile << ", ";
	    outfile << right << setw(4) << (*l3it).getP1().getZ();
	    outfile << "]";
	    outfile << "   ";
	    outfile << "[";
	    outfile << right << setw(4) << (*l3it).getP2().getX();
	    outfile << ", ";
	    outfile << right << setw(4) << (*l3it).getP2().getY();
	    outfile << ", ";
	    outfile << right << setw(4) << (*l3it).getP2().getZ();
	    outfile << "]";
	    outfile << "   ";
	    outfile << left << setw(4) << (*l3it).getScalarValue();
	    outfile << endl;
	    l3it++;
	    records++;
	  }
	}

	else if ((filter == "Line3D") && (sortby == "Point 1") && (order == "Descending")) {
	  sort(ln3dv.rbegin(), ln3dv.rend(), L3Dsortbyp1);
	  outfile << L3DHeader;
	  l3it = ln3dv.begin();

	  while (l3it != ln3dv.end()) {
	    outfile << fixed << showpoint << setprecision(3);
	    outfile << "[";
	    outfile << right << setw(4) << (*l3it).getP1().getX();
	    outfile << ", ";
	    outfile << right << setw(4) << (*l3it).getP1().getY();
	    outfile << ", ";
	    outfile << right << setw(4) << (*l3it).getP1().getZ();
	    outfile << "]";
	    outfile << "   ";
	    outfile << "[";
	    outfile << right << setw(4) << (*l3it).getP2().getX();
	    outfile << ", ";
	    outfile << right << setw(4) << (*l3it).getP2().getY();
	    outfile << ", ";
	    outfile << right << setw(4) << (*l3it).getP2().getZ();
	    outfile << "]";
	    outfile << "   ";
	    outfile << left << setw(4) << (*l3it).getScalarValue();
	    outfile << endl;
	    l3it++;
	    records++;
	  }
	}

	else if ((filter == "Line3D") && (sortby == "Point 2") && (order == "Ascending")) {
	  sort(ln3dv.begin(), ln3dv.end(), L3Dsortbyp2);
	  outfile << L3DHeader;
	  l3it = ln3dv.begin();

	  while (l3it != ln3dv.end()) {
	    outfile << fixed << showpoint << setprecision(3);
	    outfile << "[";
	    outfile << right << setw(4) << (*l3it).getP1().getX();
	    outfile << ", ";
	    outfile << right << setw(4) << (*l3it).getP1().getY();
	    outfile << ", ";
	    outfile << right << setw(4) << (*l3it).getP1().getZ();
	    outfile << "]";
	    outfile << "   ";
	    outfile << "[";
	    outfile << right << setw(4) << (*l3it).getP2().getX();
	    outfile << ", ";
	    outfile << right << setw(4) << (*l3it).getP2().getY();
	    outfile << ", ";
	    outfile << right << setw(4) << (*l3it).getP2().getZ();
	    outfile << "]";
	    outfile << "   ";
	    outfile << left << setw(4) << (*l3it).getScalarValue();
	    outfile << endl;
	    l3it++;
	    records++;
	  }
	}

	else if ((filter == "Line3D") && (sortby == "Point 2") && (order == "Descending")) {
	  sort(ln3dv.rbegin(), ln3dv.rend(), L3Dsortbyp2);
	  outfile << L3DHeader;
	  l3it = ln3dv.begin();

	  while (l3it != ln3dv.end()) {
	    outfile << fixed << showpoint << setprecision(3);
	    outfile << "[";
	    outfile << right << setw(4) << (*l3it).getP1().getX();
	    outfile << ", ";
	    outfile << right << setw(4) << (*l3it).getP1().getY();
	    outfile << ", ";
	    outfile << right << setw(4) << (*l3it).getP1().getZ();
	    outfile << "]";
	    outfile << "   ";
	    outfile << "[";
	    outfile << right << setw(4) << (*l3it).getP2().getX();
	    outfile << ", ";
	    outfile << right << setw(4) << (*l3it).getP2().getY();
	    outfile << ", ";
	    outfile << right << setw(4) << (*l3it).getP2().getZ();
	    outfile << "]";
	    outfile << "   ";
	    outfile << left << setw(4) << (*l3it).getScalarValue();
	    outfile << endl;
	    l3it++;
	    records++;
	  }
	}

	else if ((filter == "Line3D") && (sortby == "Length") && (order == "Ascending")) {
	  sort(ln3dv.begin(), ln3dv.end(), L3Dsortbyl);
	  outfile << L3DHeader;
	  l3it = ln3dv.begin();

	  while (l3it != ln3dv.end()) {
	    outfile << fixed << showpoint << setprecision(3);
	    outfile << "[";
	    outfile << right << setw(4) << (*l3it).getP1().getX();
	    outfile << ", ";
	    outfile << right << setw(4) << (*l3it).getP1().getY();
	    outfile << ", ";
	    outfile << right << setw(4) << (*l3it).getP1().getZ();
	    outfile << "]";
	    outfile << "   ";
	    outfile << "[";
	    outfile << right << setw(4) << (*l3it).getP2().getX();
	    outfile << ", ";
	    outfile << right << setw(4) << (*l3it).getP2().getY();
	    outfile << ", ";
	    outfile << right << setw(4) << (*l3it).getP2().getZ();
	    outfile << "]";
	    outfile << "   ";
	    outfile << left << setw(4) << (*l3it).getScalarValue();
	    outfile << endl;
	    l3it++;
	    records++;
	  }
	}

	else if ((filter == "Line3D") && (sortby == "Length") && (order == "Descending")) {
	  sort(ln3dv.rbegin(), ln3dv.rend(), L3Dsortbyl);
	  outfile << L3DHeader;
	  l3it = ln3dv.begin();

	  while (l3it != ln3dv.end()) {
	    outfile << fixed << showpoint << setprecision(3);
	    outfile << "[";
	    outfile << right << setw(4) << (*l3it).getP1().getX();
	    outfile << ", ";
	    outfile << right << setw(4) << (*l3it).getP1().getY();
	    outfile << ", ";
	    outfile << right << setw(4) << (*l3it).getP1().getZ();
	    outfile << "]";
	    outfile << "   ";
	    outfile << "[";
	    outfile << right << setw(4) << (*l3it).getP2().getX();
	    outfile << ", ";
	    outfile << right << setw(4) << (*l3it).getP2().getY();
	    outfile << ", ";
	    outfile << right << setw(4) << (*l3it).getP2().getZ();
	    outfile << "]";
	    outfile << "   ";
	    outfile << left << setw(4) << (*l3it).getScalarValue();
	    outfile << endl;
	    l3it++;
	    records++;
	  }
	}
}

void enterChoice() {
  string choice;
  int again = 0;

  while (again == 0) {
    cout << "Please enter your choice: ";
    cin >> choice;

    if (((choice == "2") || (choice == "3") || (choice == "4") || (choice == "5") || (choice == "6"))  && (check == 0)) {
      again = 1;
      cout << endl << "\033[1m\033[31mPlease read in data before proceeding with other options\033[0m" << endl;
      cout << "Press ENTER to return to main menu ";
      cin.ignore();
      cin.ignore();
      displayMenu();
      again = 0;
    }
    else if (choice == "1") {
      again = 1;
      one();
      check = 1;
      displayMenu();
      enterChoice();
    }
    else if (choice == "2") {
      again = 1;
      two();
      displayMenu();
      enterChoice();
    }
    else if (choice == "3") {
      again = 1;
      three();
      displayMenu();
      enterChoice();
    }
    else if (choice == "4") {
      again = 1;
      four();
      displayMenu();
      enterChoice();
    }
    else if (choice == "5") {
      again = 1;
      five();
      cout << endl;
      cout << "Press ENTER to return to main menu ";
      cin.ignore();
      cin.ignore();
      displayMenu();
      enterChoice();
    }
    else if (choice == "6") {
      again = 1;
      six();
      displayMenu();
      enterChoice();
    }
    else if (choice == "7") {
      again = 1;
      cout << "Goodbye!" << endl;
      cout << endl;
      exit(1);
    }
    else {
      again = 1;
      cout << "Please enter a choice from 1 - 7";
      cout << endl;
      cout << endl;
      again = 0;
    }
  }
}

int main() {
  displayMenu();
  enterChoice();

  return 0;
}
