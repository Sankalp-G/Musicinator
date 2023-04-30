#include <iostream>
#include <iomanip>
#include <fstream>
#include "record.h"
#include "title.h"

using namespace std;

int main() {
  cout << TITLE << "\n\n\n";

  Record rec = Record();

  rec.name = "Overdose";
  rec.artist = "natori";

  cout << rec.to_string() << endl; 

  rec.save_to_disk();

  ifstream file("./saved_records/Believer.json");
  Record loaded_record;
  loaded_record.load_from_file(file);
  cout << loaded_record.to_string() << endl;

  return 0;
}
