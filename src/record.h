#ifndef RECORD_H
#define RECORD_H

#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;

class Record {
  public:
  string name;
  string artist;

  string to_string() {
    stringstream output;
    output << setw(10) << name << setw(10) << artist;
    return output.str();
  }
};

#endif
