/*
  author: Haller Tobias
  class: 5AHIF
*/

#include <iostream>
#include <vector>
#include "CLI11.hpp"

using namespace std;

string checkValidator(const string& s){
    size_t found = s.find_first_not_of("0123456789");
    if (found != string::npos){
         throw CLI::ValidationError(s +" contains not numeric character");
    }else{
        return ""; 
    }
}

int main(int argc, char* const argv[]) {
    vector<string> input;

    CLI::App app("Factor numbers");
    app.add_option("number", input, "numbers to factor")->check(checkValidator);
    bool asy{false};
    app.add_flag("-a, --async", asy, "async");
    CLI11_PARSE(app, argc, argv);
}