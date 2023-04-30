#include <iostream>
#include "title.h"
#include "record.h"
#include <iomanip>

int main() {
  Record rec = Record();

  rec.name = "BEEP";
  rec.artist = "BOOP";

  std::cout << TITLE << std::endl;

  cout << "Something cool:" << rec.to_string() << endl; 
}
