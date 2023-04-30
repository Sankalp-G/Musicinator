#include <iostream>
#include <iomanip>
#include <fstream>
#include "record.h"
#include "title.h"
#include "record_list.h"

using namespace std;

int main() {
  cout << TITLE << "\n\n\n";

  RecordList reclist = RecordList();
  reclist.load_saved_records();
  reclist.display();

  return 0;
}
