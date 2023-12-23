#include "operation.h"

int main() {
    int key;
    do {
        cout << "Choose type of data: " << endl;
        cout << "1 - [ - Integers -]" << endl;
        cout << "2 - [ - Float - ]" << endl;
        cout << "0 - [ - Exit - ]" << endl;
     cin >> key;

        switch (key) {
        case 1: {
            InterfaceInt();
            break;
        }
        case 2: {
            InterfaceFloat();
            break;
        }
        case 0:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    } while (key != 0);

    return 0;
}