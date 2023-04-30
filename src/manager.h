#ifndef MANAGER_H
#define MANAGER_H

#include <iostream>
#include "record_list.h"
#include "title.h"

using namespace std;

class Manager {
  public:
  void main_menu() {
    display_main_menu_prompt();

    int choice = query_num_between(1, 4);

    switch(choice) {
      case 1:
        view_records();
        break;
      case 4:
        exit(0);
    }
  }

  void display_main_menu_prompt() {
    clear_terminal();
    cout << TITLE << "\n\n\n";

    cout << \
    R"(What would you like to do?
    1] View Saved records
    2] Add new record
    3] Withdraw a record
    4] Exit)" << "\n\n";
  }

  void view_records() {
    clear_terminal();

    cout << "The following records are currently available: " << "\n\n";
    RecordList record_list;
    record_list.load_saved_records();
    record_list.display();

    cout << "\n" << "Press any key to continue...";
    getchar();
    getchar();
    main_menu();
  }

  private:
  int query_num_between(int lower, int higher) {
    int input_num;

    cout << "> ";
    while (true) {
      cin >> input_num;

      if (input_num >= lower && input_num <= higher) {
        return input_num;
      }

      cout << "Invalid: Enter an integer between " << lower << " and " << higher << endl;
      cout << "Try again: ";
    }
  }

  void clear_terminal() {
      // CSI[2J clears screen, CSI[H moves the cursor to top-left corner
      std::cout << "\x1B[2J\x1B[H";
  }
};

#endif