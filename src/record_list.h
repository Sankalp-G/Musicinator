#ifndef RECORD_LIST_H
#define RECORD_LIST_H

#include <vector>
#include <iostream>
#include <filesystem>
#include "record.h"

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
    for (auto rec = records.begin(); rec != records.end(); ++rec)
        cout << rec->to_string() << endl;
  }
};

#endif
