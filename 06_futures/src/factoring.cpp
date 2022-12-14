/*
  author: Haller Tobias
  class: 5AHIF
*/

#include <iostream>

using namespace std;

int main(int argc, char* const argv[]) {
    for (int i=1; i < argc; i++) {
        cout << argv[i] << endl;
    }
}