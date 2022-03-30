//
// Created by catfood on 2/21/2022.
//

#include "lunchLine.h"
#include <list>
#include <string>
#include<iostream>
using namespace std;

lunchLine::lunchLine() {}

void lunchLine::main() {
    list<string> name;
    list<string>::iterator iter = name.begin();
    int choice;
    char playagain = 'y';

    choices(name,iter,2);
    while (true) {
        cout << "[1] Lunch Lady\n[2] Print\n[3] Sign Up\n[4] Cut\n[5] Teacher\n[6] Bell\n[7] Quit\nEnter Selection >> ";
        cin >> choice;
        if (choice == 7)
            break;
        cin.clear();
        cin.sync();
        choices(name, iter, choice);
        choices(name, iter, 2);
        cout << "Do you wish to play again? [Y] for yes > ";
        cin >> playagain;
    }
}

void lunchLine::choices(list<string> &name, list<string>::iterator iter, int choice) {
    string person;
    string place;

        switch (choice) {
            case 1: // Lunch Lady
                if (!name.empty())
                    name.pop_front();
                break;
            case 2: // NEED TO ENTER NAME
                for (iter = name.begin(); iter != name.end(); iter++) {
                    cout << *iter << endl;
                }
                break;
            case 3: // Sign Up
                cout << "Enter name >> ";
                getline(cin, person);
                name.push_front(person);
                break;
            case 4: //
                cout << "Enter name >> ";
                getline(cin, person);
                cout << "Person to cut >> ";
                getline(cin, place);
                for (iter = name.begin(); iter != name.end(); iter++) {
                    if (*iter == place)
                        name.insert(iter, person);
                }
                break;
            case 5: // Teacher
                cout << "Enter name >> ";
                getline(cin, person);
                for (iter = name.begin(); iter != name.end(); iter++) {
                    if (*iter == person) {
                        name.erase(iter);
                        break;
                    }
                }
                name.push_back(person);
                break;
            case 6: // Bell
                name.clear();
                break;
        }
    }

lunchLine::~lunchLine() {}
