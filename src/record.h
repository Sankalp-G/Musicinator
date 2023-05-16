#ifndef RECORD_H
#define RECORD_H

#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>

#include "constants.h"
#include "../libraries/json.hpp"

using namespace std;
using json = nlohmann::json;

class Record {
  public:
  string name;
  string artist;
  int count;

  Record() {}

  Record(string name, string artist, int count) {
    this->name = name;
    this->artist = artist;
    this->count = count;
  }

  void get_data_from_user() {
    cout << "Enter record data:" << endl;
    cout << "  Name: ";
    getline(cin, name);
    cout << "  Artist name: ";
    getline(cin, artist);
    cout << "  Record count: ";
    cin >> count;
    cin.ignore(256, '\n');
  }

  json to_json() {
    return {
      {"name", name},
      {"artist", artist},
      {"count", count}
    };
  }

  void load_from_file(ifstream &fileptr) {
    json json_data = json::parse(fileptr);

    name = json_data["name"];
    artist = json_data["artist"];
    count = json_data["count"];
  }

  void save_to_disk() {
    ofstream fileptr(file_path());
    fileptr << to_json().dump(4);

    fileptr.close();
    cout << "Saved record successfully" << endl;
  }

  private:
  string file_path() {
    stringstream path;
    path << "./saved_records/" << name << ".json";

    return path.str();
  }
};

#endif
