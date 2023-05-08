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
      case 2:
        save_new_record();
        break;
      case 3:
        withdraw_records();
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

  void return_prompt() {
    cout << "\nPress any key to continue...";
    getchar();
    main_menu();
  }

  void view_records() {
    clear_terminal();

    cout << "The following records are currently available: " << "\n\n";
    RecordList record_list;
    record_list.load_saved_records();
    record_list.display();

    return_prompt();
  }

  void save_new_record() {
    clear_terminal();

    Record rec;
    rec.get_data_from_user();
    rec.save_to_disk();

    return_prompt();
  }

  void withdraw_records() {
    clear_terminal();
    RecordList record_list;
    record_list.load_saved_records();
    record_list.display();

    cout << "\nWhich record would you like to retrieve (#): ";
    int selection = query_num_between(1, record_list.records.size());

    Record selected_record = record_list.records.at(selection - 1);

    cout << "\nHow many would you like to retrieve: ";
    int retrieve_amount = query_num_between(0, selected_record.count);

    selected_record.count -= retrieve_amount;
    selected_record.save_to_disk();

    return_prompt();
  }

  private:
  int query_num_between(int lower, int higher) {
    int input_num;

    cout << "> ";
    while (true) {
      cin >> input_num;

      if (input_num >= lower && input_num <= higher) {
        cin.ignore(256, '\n');
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
