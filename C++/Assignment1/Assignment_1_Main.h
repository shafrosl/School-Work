//g++ -std=c++11 Assignment_1_Main.cpp -o A1.exe
//./A1.exe

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;
vector <string> xAxis;
vector <string> yAxis;
vector <string> id;
vector <string> rainHML;
string ** array2D = nullptr;
int check = 0;

void displayMenu();
void enterChoice();

// structs for information from .txt files to be stored in
struct city {
  string position;
  string id;
  string name;
};

struct cloud {
  string position;
  string forecast;
};

struct press {
  string position;
  string forecast;
};

vector <city> cityLocation;
vector <cloud> cloudCover;
vector <press> pressure;

// main part of programme
int main() {
  displayMenu();
  enterChoice();

  return 0;
}

// displays menu
void displayMenu() {
  cout << endl;
  cout << "\033[0;34mStudent ID: 10193369/6098253" << endl;
  cout << "Student Name: Mohamed Shafiq Bin Roslan\033[0m" << endl;
  cout << "---------------------------------------------" << endl;
  cout << "Welcome to Weather Information Processing System!" << endl;
  cout << endl;
  cout << "1.     Read in and process a configuration file" << endl;
  cout << "2.     Display city map" << endl;
  cout << "3.     Display cloud coverage map (cloudiness index)" << endl;
  cout << "4.     Display cloud coverage map (LMH symbols)" << endl;
  cout << "5.     Display atmospheric pressure map (pressure index)" << endl;
  cout << "6.     Display atmospheric pressure map (LMH symbols)" << endl;
  cout << "7.     Show weather forecast summary report" << endl;
  cout << "8.     Quit" << endl;
  cout << endl;
}

// choice selected from the menu shown
void enterChoice() {
  string choice;
  int again = 0;
  void displayMenu();
  void enterChoice();
  void pressEnter();
  void openFile();
  void createMap(int x, int y);
  void displayMap(int x, int y);
  void deallocate(int x, int y);
  void cityMap();
  void cloudIndex();
  void cloudIndexLMH();
  void pressMap();
  void pressMapLMH();
  void acc(string a);
  void ap(string a);
  void storeid();
  void rain();
  vector <string> tokenizeString(string input, string delimiter);

  // loop to re-enter choice
  while (again == 0) {
    cout << "Please enter your choice: ";
    cin >> choice;

    // choice 1: opens the file and stores the info into structs and vectors
    try {
      if (choice == "1") {
        again = 1;
        check = 1;
        cout << "[Read in and process a configuration file]" << endl;
        openFile();
        displayMenu();
        enterChoice();
      }

      // choice 2 - 6: creates and displays maps with the info taken in
      // deallocates the memory to be used by other choices
      else if (choice == "2") {
        if (check == 1) { // checks if config file is read in
          again = 1;
          cout << "[Display city map]" << endl;
          cout << endl;
          createMap(stoi(yAxis[1]), stoi(xAxis[1]));
          cityMap();
    		  displayMap(stoi(yAxis[1]), stoi(xAxis[1]));
          cout << endl;
          cout << "Press ENTER to return to main menu ";
          cin.ignore();
          cin.ignore();
          displayMenu();
          enterChoice();
          deallocate(stoi(yAxis[1]), stoi(xAxis[1]));
        }
        else {
          throw 'a';
        }
      }

      else if (choice == "3") {
        if (check == 1) {
          again = 1;
          cout << "[Display cloud coverage map (cloudiness index)]" << endl;
          cout << endl;
          createMap(stoi(yAxis[1]), stoi(xAxis[1]));
          cloudIndex();
  		    displayMap(stoi(yAxis[1]), stoi(xAxis[1]));
          cout << endl;
          cout << "Press ENTER to return to main menu ";
          cin.ignore();
          cin.ignore();
          displayMenu();
          enterChoice();
          deallocate(stoi(yAxis[1]), stoi(xAxis[1]));
        }
        else {
          throw 'a';
        }
      }

      else if (choice == "4") {
        if (check == 1) {
          again = 1;
          cout << "[Display cloud coverage map (LMH symbols)]" << endl;
          cout << endl;
          createMap(stoi(yAxis[1]), stoi(xAxis[1]));
          cloudIndexLMH();
  		    displayMap(stoi(yAxis[1]), stoi(xAxis[1]));
          cout << endl;
          cout << "Press ENTER to return to main menu ";
          cin.ignore();
          cin.ignore();
          displayMenu();
          enterChoice();
          deallocate(stoi(yAxis[1]), stoi(xAxis[1]));
        }
        else {
          throw 'a';
        }
      }

      else if (choice == "5") {
        if (check == 1) {
          again = 1;
          cout << "[Display atmospheric pressure map (pressure index)]" << endl;
          cout << endl;
          createMap(stoi(yAxis[1]), stoi(xAxis[1]));
          pressMap();
  		    displayMap(stoi(yAxis[1]), stoi(xAxis[1]));
          cout << endl;
          cout << "Press ENTER to return to main menu ";
          cin.ignore();
          cin.ignore();
          displayMenu();
          enterChoice();
          deallocate(stoi(yAxis[1]), stoi(xAxis[1]));
        }
        else {
          throw 'a';
        }
      }

      else if (choice == "6") {
        if (check == 1) {
          again = 1;
          cout << "[Display atmospheric pressure map (LMH symbols)]" << endl;
          cout << endl;
          createMap(stoi(yAxis[1]), stoi(xAxis[1]));
          pressMapLMH();
  		    displayMap(stoi(yAxis[1]), stoi(xAxis[1]));
          cout << endl;
          cout << "Press ENTER to return to main menu ";
          cin.ignore();
          cin.ignore();
          displayMenu();
          enterChoice();
          deallocate(stoi(yAxis[1]), stoi(xAxis[1]));
        }
        else {
          throw 'a';
        }
      }

      // choice 7: shows the summary from the information extracted
      else if (choice == "7") {
        if (check == 1) {
          again = 1;
          cout << "[Show weather forecast summary report]" << endl;
          cout << endl;
          storeid();

          for (auto it = begin(id); it != end(id); ++it) {
            string i = (*it);
            vector<string> temp = tokenizeString(i, "-");
            cout << "\033[0;32mCity Name  \033[0m: " << temp[1] << endl;
            cout << "\033[0;32mCity ID    \033[0m: " << temp[0] << endl;
            acc(temp[0]);
            ap(temp[0]);
            rain();
            cout << endl;
          }
          cout << "Press ENTER to return to main menu ";
          cin.ignore();
          cin.ignore();
          displayMenu();
          enterChoice();
        }
        else {
          throw 'a';
        }
      }

      // choice 8: exits the programme
      else if (choice == "8") {
        again = 1;
        cout << endl;
        cout << "Goodbye!" << endl;
        exit(1);
      }
      else {
        throw 5;
      }
    }

    catch (int a) {
      cout << endl;
      cout << "An error occurred" << endl;
      cout << "Please enter a valid choice (1 - 8)" << endl;
      cout << endl;
      cin.clear();
      cin.ignore();
    }
    catch (char a) {
      cout << endl;
      cout << "An error occurred" << endl;
      cout << "Please input a configuration file first" << endl;
      cout << endl;
      cin.clear();
      cin.ignore();
    }
  }
}

//opens the file and reads in the information from the .txt file
void openFile() {
  string file;
  string aLine;
  vector <string> info;
  vector <string> tempv;
  vector <string> temp;
  vector <string> readFile(string filename);
  vector <string> tokenizeString(string input, string delimiter);

  cout << endl;
  while (file != "config.txt") {
    cout << "Please enter file name: ";
    cin >> file;
  }

	cout << endl;
	cout << "Reading contents of " << file << "..." << endl;

  fstream inputFile(file.c_str(), fstream::in);

  // ignores empty lines and lines that starts with '/'
  while (getline(inputFile, aLine)) {
    if ((aLine.length() > 0) && aLine[0] != '/') {
      info.push_back(aLine);
    }
	}

  vector <string> splitX = tokenizeString(info[0], "=");
  vector <string> splitY = tokenizeString(info[1], "=");

  cout << "Reading in " << splitX[0] << ": " << splitX[1];
  cout << "...success!" << endl;
  cout << "Reading in " << splitY[0] << ": " << splitY[1];
	cout << "...success!" << endl;
  cout << endl;

  string cityFile = info[2];
  string cloudFile = info[3];
  string pressureFile = info[4];

  //store city info
  cityLocation.clear();
  tempv = readFile(cityFile);

  for (auto it = begin(tempv); it != end(tempv); ++it) {
    vector <string> temp = tokenizeString(*it, "-");
    city city;
    city.position = temp[0];
    city.id = temp[1];
    city.name = temp[2];
    cityLocation.push_back(city);
 }
 tempv.clear();

  //store cloud info
  cloudCover.clear();
  tempv = readFile(cloudFile);

  for (auto it = begin(tempv); it != end(tempv); ++it) {
    vector <string> temp = tokenizeString(*it, "-");
    cloud cloud;
    cloud.position = temp[0];
    cloud.forecast = temp[1];
    cloudCover.push_back(cloud);
 }
 tempv.clear();

  //store pressure info
  pressure.clear();
  tempv = readFile(pressureFile);

  for (auto it = begin(tempv); it != end(tempv); ++it) {
    vector <string> temp = tokenizeString(*it, "-");
    press press;
    press.position = temp[0];
    press.forecast = temp[1];
    pressure.push_back(press);
 }
 tempv.clear();

  xAxis = tokenizeString(splitX[1], "-");
  yAxis = tokenizeString(splitY[1], "-");

  cout << "All records stored. Returning to main menu..." << endl;
}

// reads file and stores the information into a vector
vector <string> readFile(string file) {
  vector <string> info;

  fstream inputFile(file.c_str(), fstream::in);

	cout << "Reading contents of " << file << "...";

	string aLine;

  while (getline(inputFile, aLine)) {
    if (aLine.length() > 0) {
      info.push_back(aLine);
    }
	}

  cout << "success!" << endl;
  cout << endl;

  return info;
}

// splits the string into segments depending on what delimiter is given
vector <string> tokenizeString(string input, string delimiter) {
	size_t pos = 0;
	string token;
	vector <string> result;

	while ((pos = input.find(delimiter)) != string::npos) {
    token = input.substr(0, pos);
    result.push_back(token);
		input.erase(0, pos + delimiter.length());
	}

	result.push_back(input);

	return result;
}

// creates an empty map with dimensions extracted from .txt file
void createMap(int x, int y) {
  int row = x + 4;
  int col = y + 4;
  array2D = new string * [row];
  int xcount = 0;
  int ycount = 0;

  for (int i = 0; i < row; i++) {
    array2D[i] = new string [col];
  }

  for (int i = row-1; i > -1; i--) {
    for (int j = 0; j < col; j++) {
      if ((i == row-1) && ((1 < j) && (j < col-1))) {
        array2D[i][j] = to_string(xcount);
        xcount++;
      }
      else if (((i < row-2) && (0 < i)) && (j == 0)) {
        array2D[i][j] = to_string(ycount);
        ycount++;
      }
      else if ((i == row-2) && (j > 0)) {
        array2D[i][j] = "# ";
      }
      else if ((i == 0) && (j > 0)) {
        array2D[i][j] = "# ";
      }
      else if ((i < row-1) && (j == 1)) {
        array2D[i][j] = "# ";
      }
      else if ((i < row-1) && (j == col-1)) {
        array2D[i][j] = "# ";
      }
      else {
        array2D[i][j] = "  ";
      }
    }
  }
}

// displays the map with formatting
void displayMap(int x, int y) {
  int row = x + 4;
  int col = y + 4;

  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      cout << left;
      cout << setw(2) << array2D[i][j] << " ";
    }
    cout << endl;
  }
}

// deallocates from the 2d array
void deallocate(int x, int y) {
  if (x <= 0) {
    return;
  }

  for (int i = 0; i < y; i++) {
    delete[] array2D[i];
  }

  delete[] array2D;
}

// converts .txt x-coordinates to 2darray coordinates
int xcoo(string c) {
  int i = stoi(c);
  i += 2;

  return i;
}

// converts .txt y-coordinates to 2darray coordinates
int ycoo(string c) {
  int i = stoi(c);
  int j = (stoi(yAxis[1]));
  return (j-i+1);
}

// converts 2darray coordinates to .txt x-coordinates
string revx(int c) {
  c -= 2;
  string i = to_string(c);

  return i;
}

// converts 2darray coordinates to .txt x-coordinates
string revy(int c) {
  int j = (stoi(yAxis[1]));
  string i = to_string(j-c+1);

  return i;
}

// plots the info for the city map
void cityMap() {
  int xcoo(string c);
  int ycoo(string c);

  for (auto it = begin(cityLocation); it != end(cityLocation); ++it) {
    string p = (*it).position;
    size_t a = p.find(",");
    size_t b = p.find(" ");
    size_t c = p.find("]");
    p.erase(c);
    string x = p.substr(1, a-1);
    string y = p.substr(b+1);
    array2D[ycoo(y)][xcoo(x)] = (*it).id;
  }
}

// plots the info for cloud index
void cloudIndex() {
  int xcoo(string c);
  int ycoo(string c);

  for (auto it = begin(cloudCover); it != end(cloudCover); ++it) {
    string p = (*it).position;
    size_t a = p.find(",");
    size_t b = p.find(" ");
    size_t c = p.find("]");
    p.erase(c);
    string x = p.substr(1, a-1);
    string y = p.substr(b+1);

    if (stoi((*it).forecast) < 10) {
      array2D[ycoo(y)][xcoo(x)] = "0";
    }
    else if (stoi((*it).forecast) < 20) {
      array2D[ycoo(y)][xcoo(x)] = "1";
    }
    else if (stoi((*it).forecast) < 30) {
      array2D[ycoo(y)][xcoo(x)] = "2";
    }
    else if (stoi((*it).forecast) < 40) {
      array2D[ycoo(y)][xcoo(x)] = "3";
    }
    else if (stoi((*it).forecast) < 50) {
      array2D[ycoo(y)][xcoo(x)] = "4";
    }
    else if (stoi((*it).forecast) < 60) {
      array2D[ycoo(y)][xcoo(x)] = "5";
    }
    else if (stoi((*it).forecast) < 70) {
      array2D[ycoo(y)][xcoo(x)] = "6";
    }
    else if (stoi((*it).forecast) < 80) {
      array2D[ycoo(y)][xcoo(x)] = "7";
    }
    else if (stoi((*it).forecast) < 90) {
      array2D[ycoo(y)][xcoo(x)] = "8";
    }
    else {
      array2D[ycoo(y)][xcoo(x)] = "9";
    }
  }
}

// plots the info for cloud index in LMH form
void cloudIndexLMH() {
  int xcoo(string c);
  int ycoo(string c);

  for (auto it = begin(cloudCover); it != end(cloudCover); ++it) {
    string p = (*it).position;
    size_t a = p.find(",");
    size_t b = p.find(" ");
    size_t c = p.find("]");
    p.erase(c);
    string x = p.substr(1, a-1);
    string y = p.substr(b+1);

    if (stoi((*it).forecast) < 35) {
      array2D[ycoo(y)][xcoo(x)] = "L";
    }
    else if (stoi((*it).forecast) < 65) {
      array2D[ycoo(y)][xcoo(x)] = "M";
    }
    else {
      array2D[ycoo(y)][xcoo(x)] = "H";
    }
  }
}

// plots info for pressure index
void pressMap() {
  int xcoo(string c);
  int ycoo(string c);

  for (auto it = begin(pressure); it != end(pressure); ++it) {
    string p = (*it).position;
    size_t a = p.find(",");
    size_t b = p.find(" ");
    size_t c = p.find("]");
    p.erase(c);
    string x = p.substr(1, a-1);
    string y = p.substr(b+1);

    if (stoi((*it).forecast) < 10) {
      array2D[ycoo(y)][xcoo(x)] = "0";
    }
    else if (stoi((*it).forecast) < 20) {
      array2D[ycoo(y)][xcoo(x)] = "1";
    }
    else if (stoi((*it).forecast) < 30) {
      array2D[ycoo(y)][xcoo(x)] = "2";
    }
    else if (stoi((*it).forecast) < 40) {
      array2D[ycoo(y)][xcoo(x)] = "3";
    }
    else if (stoi((*it).forecast) < 50) {
      array2D[ycoo(y)][xcoo(x)] = "4";
    }
    else if (stoi((*it).forecast) < 60) {
      array2D[ycoo(y)][xcoo(x)] = "5";
    }
    else if (stoi((*it).forecast) < 70) {
      array2D[ycoo(y)][xcoo(x)] = "6";
    }
    else if (stoi((*it).forecast) < 80) {
      array2D[ycoo(y)][xcoo(x)] = "7";
    }
    else if (stoi((*it).forecast) < 90) {
      array2D[ycoo(y)][xcoo(x)] = "8";
    }
    else {
      array2D[ycoo(y)][xcoo(x)] = "9";
    }
  }
}

// plots info for pressure index in LMH form
void pressMapLMH() {
  int xcoo(string c);
  int ycoo(string c);

  for (auto it = begin(pressure); it != end(pressure); ++it) {
    string p = (*it).position;
    size_t a = p.find(",");
    size_t b = p.find(" ");
    size_t c = p.find("]");
    p.erase(c);
    string x = p.substr(1, a-1);
    string y = p.substr(b+1);

    if (stoi((*it).forecast) < 35) {
      array2D[ycoo(y)][xcoo(x)] = "L";
    }
    else if (stoi((*it).forecast) < 65) {
      array2D[ycoo(y)][xcoo(x)] = "M";
    }
    else {
      array2D[ycoo(y)][xcoo(x)] = "H";
    }
  }
}

// calculates total average of cloud coverage of cities and the cells surrounding it
void acc(string a) {
  int total = 0;
  double accu = 0;
  void createMap(int x, int y);
  void cityMap();
  void deallocate(int x, int y);
  vector<string> pos;
  string revx(int c);
  string revy(int c);

  createMap(stoi(yAxis[1]), stoi(xAxis[1]));
  cityMap();

  // looks for the coordinates of the cities and the cells surrounding the city
  for (int i = 1; i < (stoi(yAxis[1]))+2; i++) {
    for (int j = 2; j < (stoi(xAxis[1]))+3; j++) {

      int ia = i+1;
      int ib = i-1;
      int ja = j+1;
      int jb = j-1;

      // [x][y]
      if (array2D[i][j] == a) {
        string s = "[" + revx(j) + ", " + revy(i) + "]";
        pos.push_back(s);
        total++;
      }
      else if ((ia < stoi(yAxis[1])+2) ||
              (ib > -1) ||
              (ja < stoi(xAxis[1])+3) ||
              (jb > 1)) {
        // [x][y+1]
        if (array2D[ia][j] == a) {
          string s = "[" + revx(j) + ", " + revy(i) + "]";
          pos.push_back(s);
          total++;
        }
        // [x][y-1]
        else if (array2D[ib][j] == a) {
          string s = "[" + revx(j) + ", " + revy(i) + "]";
          pos.push_back(s);
          total++;
        }
        // [x+1][y]
        else if (array2D[i][ja] == a) {
          string s = "[" + revx(j) + ", " + revy(i) + "]";
          pos.push_back(s);
          total++;
        }
        // [x-1][y]
        else if (array2D[i][jb] == a) {
          string s = "[" + revx(j) + ", " + revy(i) + "]";
          pos.push_back(s);
          total++;
        }
        // [x+1][y+1]
        else if (array2D[ia][ja] == a) {
          string s = "[" + revx(j) + ", " + revy(i) + "]";
          pos.push_back(s);
          total++;
        }
        // [x-1][y+1]
        else if (array2D[ia][jb] == a) {
          string s = "[" + revx(j) + ", " + revy(i) + "]";
          pos.push_back(s);
          total++;
        }
        // [x-1][y-1]
        else if (array2D[ib][jb] == a) {
          string s = "[" + revx(j) + ", " + revy(i) + "]";
          pos.push_back(s);
          total++;
        }
        // [x+1][y-1]
        else if (array2D[ib][ja] == a) {
          string s = "[" + revx(j) + ", " + revy(i) + "]";
          pos.push_back(s);
          total++;
        }
      }
    }
  }

  // extracts the cloud index of the cells that are part of the city
  for (auto ip = begin(pos); ip != end(pos); ++ip) {
    for (auto ic = begin(cloudCover); ic != end(cloudCover); ++ic) {
      string p = (*ip);
      string c = (*ic).position;
      string f = (*ic).forecast;
      if (p == c) {
        accu += stoi(f);
      }
      else {
        continue;
      }
    }
  }

  double acc = (accu/total);

  string symb;

  if (acc < 35) {
    symb = "(L)";
  }
  else if (acc < 65) {
    symb = "(M)";
  }
  else {
    symb = "(H)";
  }

  rainHML.push_back(symb);

  cout << "\033[0;35mAve. Cloud Cover \033[0;0m(\033[1;35mACC\033[21;0m)     : " << fixed << setprecision(2) << acc << " " << symb << endl;

  deallocate(stoi(yAxis[1]), stoi(xAxis[1]));
}

// calculates total average of pressure index
void ap(string a) {
  int total = 0;
  double accu = 0;
  void createMap(int x, int y);
  void cityMap();
  void deallocate(int x, int y);
  vector<string> pos;
  string revx(int c);
  string revy(int c);

  createMap(stoi(yAxis[1]), stoi(xAxis[1]));
  cityMap();

  // looks for the cities and the cells surrounding it
  for (int i = 1; i < (stoi(yAxis[1]))+2; i++) {
    for (int j = 2; j < (stoi(xAxis[1]))+3; j++) {

      int ia = i+1;
      int ib = i-1;
      int ja = j+1;
      int jb = j-1;

      // [x][y]
      if (array2D[i][j] == a) {
        string s = "[" + revx(j) + ", " + revy(i) + "]";
        pos.push_back(s);
        total++;
      }
      else if ((ia < stoi(yAxis[1])+2) ||
              (ib > -1) ||
              (ja < stoi(xAxis[1])+3) ||
              (jb > 1)) {
        // [x][y+1]
        if (array2D[ia][j] == a) {
          string s = "[" + revx(j) + ", " + revy(i) + "]";
          pos.push_back(s);
          total++;
        }
        // [x][y-1]
        else if (array2D[ib][j] == a) {
          string s = "[" + revx(j) + ", " + revy(i) + "]";
          pos.push_back(s);
          total++;
        }
        // [x+1][y]
        else if (array2D[i][ja] == a) {
          string s = "[" + revx(j) + ", " + revy(i) + "]";
          pos.push_back(s);
          total++;
        }
        // [x-1][y]
        else if (array2D[i][jb] == a) {
          string s = "[" + revx(j) + ", " + revy(i) + "]";
          pos.push_back(s);
          total++;
        }
        // [x+1][y+1]
        else if (array2D[ia][ja] == a) {
          string s = "[" + revx(j) + ", " + revy(i) + "]";
          pos.push_back(s);
          total++;
        }
        // [x-1][y+1]
        else if (array2D[ia][jb] == a) {
          string s = "[" + revx(j) + ", " + revy(i) + "]";
          pos.push_back(s);
          total++;
        }
        // [x-1][y-1]
        else if (array2D[ib][jb] == a) {
          string s = "[" + revx(j) + ", " + revy(i) + "]";
          pos.push_back(s);
          total++;
        }
        // [x+1][y-1]
        else if (array2D[ib][ja] == a) {
          string s = "[" + revx(j) + ", " + revy(i) + "]";
          pos.push_back(s);
          total++;
        }
      }
    }
  }

  // extracts the pressure index out of the cities and the cells around it
  for (auto ip = begin(pos); ip != end(pos); ++ip) {
    for (auto ic = begin(pressure); ic != end(pressure); ++ic) {
      string p = (*ip);
      string c = (*ic).position;
      string f = (*ic).forecast;
      if (p == c) {
        accu += stoi(f);
      }
      else {
        continue;
      }
    }
  }

  double ap = (accu/total);

  string symb;

  if (ap < 35) {
    symb = "(L)";
  }
  else if (ap < 65) {
    symb = "(M)";
  }
  else {
    symb = "(H)";
  }

  rainHML.push_back(symb);

  cout << "\033[0;35mAve. Pressure \033[0;0m(\033[1;35mAP\033[21;0m)         : " << fixed << setprecision(2) << ap << " " << symb << endl;

  deallocate(stoi(yAxis[1]), stoi(xAxis[1]));
}

// finds unique city id and stores the id and city name into vector
void storeid() {
  for (auto it = begin(cityLocation); it != end(cityLocation); ++it) {
    string i = (*it).id;
    string n = (*it).name;
    id.push_back(i + "-" + n);
  }

  sort(id.begin(), id.end());
  id.erase(unique(id.begin(), id.end()), id.end());
}

// calculates the chance of rain in regards to pressure and cloud index
void rain() {
  if ((rainHML[0] == "(L)") && (rainHML[1] == "(H)")) {
    cout << "\033[0;34mProbability of Rain \033[0m(%)    : 90.00" << endl;
    cout << "\033[0;34m~~~~" << endl;
    cout << "~~~~~" << endl;
    cout << "\\\\\\\\\\\033[0m" << endl;
  }
  else if ((rainHML[0] == "(L)") && (rainHML[1] == "(M)")) {
    cout << "\033[0;34mProbability of Rain \033[0m(%)    : 80.00" << endl;
    cout << "\033[0;34m~~~~" << endl;
    cout << "~~~~~" << endl;
    cout << " \\\\\\\\\033[0m" << endl;
  }
  else if ((rainHML[0] == "(L)") && (rainHML[1] == "(L)")) {
    cout << "\033[0;34mProbability of Rain \033[0m(%)    : 70.00" << endl;
    cout << "\033[0;34m~~~~" << endl;
    cout << "~~~~~" << endl;
    cout << "  \\\\\\\033[0m" << endl;
  }
  else if ((rainHML[0] == "(M)") && (rainHML[1] == "(H)")) {
    cout << "\033[0;34mProbability of Rain \033[0m(%)    : 60.00" << endl;
    cout << "\033[0;34m~~~~" << endl;
    cout << "~~~~~" << endl;
    cout << "   \\\\\033[0m" << endl;
  }
  else if ((rainHML[0] == "(M)") && (rainHML[1] == "(M)")) {
    cout << "\033[0;34mProbability of Rain \033[0m(%)    : 50.00" << endl;
    cout << "\033[0;34m~~~~" << endl;
    cout << "~~~~~" << endl;
    cout << "    \\\033[0m" << endl;
  }
  else if ((rainHML[0] == "(M)") && (rainHML[1] == "(L)")) {
    cout << "\033[0;34mProbability of Rain \033[0m(%)    : 40.00" << endl;
    cout << "\033[0;34m~~~~" << endl;
    cout << "~~~~~\033[0m" << endl;
  }
  else if ((rainHML[0] == "(H)") && (rainHML[1] == "(H)")) {
    cout << "\033[0;34mProbability of Rain \033[0m(%)    : 30.00" << endl;
    cout << "\033[0;34m~~~" << endl;
    cout << "~~~~\033[0m" << endl;
  }
  else if ((rainHML[0] == "(H)") && (rainHML[1] == "(M)")) {
    cout << "\033[0;34mProbability of Rain \033[0m(%)    : 20.00" << endl;
    cout << "\033[0;34m~~" << endl;
    cout << "~~~\033[0m" << endl;
  }
  else if ((rainHML[0] == "(H)") && (rainHML[1] == "(L)")) {
    cout << "\033[0;34mProbability of Rain \033[0m(%)    : 10.00" << endl;
    cout << "\033[0;34m~" << endl;
    cout << "~~\033[0m" << endl;
  }

  rainHML.clear();
}
