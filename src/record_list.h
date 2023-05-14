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

    string row_string;
    for (int i = 0; i < records.size(); i++) {
      row_string = record_row_with_index(records.at(i), i);
      cout << row_string << endl;
    }
  }

  protected:
  virtual int full_row_width() {
    return COLUMN_WIDTH * 3 + 1;
  }

  virtual string column_titles() {
    stringstream titles;
    titles << "#" << setw(COLUMN_WIDTH) << "Title" << setw(COLUMN_WIDTH) << "Artist" << setw(COLUMN_WIDTH) << "Count" << endl;
    return titles.str();
  }

  string list_header() {
    stringstream header;
    header << column_titles();

    header << setfill('-') << setw(full_row_width()) << "-" << endl;
    return header.str();
  }

  string record_row_with_index(Record rec, int index) {
    stringstream output;

    int index_width = ((index + 1) / 10) + 1;
    output << index + 1 << setw(full_row_width() - index_width) << record_row_format(rec);
    return output.str();
  }

  virtual string record_row_format(Record rec) {
    stringstream output;
    output << rec.name << setw(COLUMN_WIDTH) << rec.artist << setw(COLUMN_WIDTH) << rec.count;
    return output.str();
  }
};

#endif
