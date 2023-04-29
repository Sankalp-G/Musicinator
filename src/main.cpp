#include <iostream>
#include "./custom_menu.h"

int main() {
  std::vector<std::string> entries = {
    "View available tracks",
    "Add new track",
    "Withdraw tracks",
    "Search for new tracks"
  };

  int selected = CustomMenu(entries);

  std::cout << "Selected index is: " <<  selected << std::endl;
}
