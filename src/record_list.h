#ifndef RECORD_LIST_H
#define RECORD_LIST_H

#include <vector>
#include <iostream>
#include <filesystem>
#include <sstream>
#include <iomanip>
#include "record.h"
#include "constants.h"

namespace fs = std::filesystem;

class RecordList {
  public:
  vector<Record> records;

  void load_saved_records() {
    Record rec;
    ifstream f;

    // go through each file in saved_records directory and add record to vector
    std::string path = "./saved_records/";
    for (const auto & entry : fs::directory_iterator(path)) {
      f = ifstream(entry.path());
      rec.load_from_file(f);
      records.push_back(rec);
    }
  }

  void display() {
    cout << list_header();

    for (int i = 0; i < records.size(); i++)
        cout << i + 1 << records.at(i).to_string() << endl;
  }

  private:
  string list_header() {
    stringstream header;
    header << "#" << setw(COLUMN_WIDTH) << "Title" << setw(COLUMN_WIDTH) << "Artist" << endl;

    int separator_width = COLUMN_WIDTH * 2 + 1;
    header << setfill('-') << setw(separator_width) << "-" << endl;
    return header.str();
  }
};

#endif
