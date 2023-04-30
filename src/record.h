#ifndef RECORD_H
#define RECORD_H

#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include "../libraries/json.hpp"

using namespace std;
using json = nlohmann::json;

class Record {
  public:
  string name;
  string artist;

  string to_string() {
    stringstream output;
    output << setw(25) << name << setw(25) << artist;
    return output.str();
  }

  json to_json() {
    return {
      {"name", name},
      {"artist", artist},
    };
  }

  void load_from_file(ifstream &fileptr) {
    json json_data = json::parse(fileptr);

    name = json_data["name"];
    artist = json_data["artist"];
  }

  void save_to_disk() {
    ofstream fileptr(file_path());

    fileptr << to_json().dump(4);
  }

  private:
  string file_path() {
    stringstream path;
    path << "./saved_records/" << name << ".json";

    return path.str();
  }
};

#endif
