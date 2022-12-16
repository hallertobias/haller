/*
  author: Haller Tobias
  class: 5AHIF
*/

#include <iostream>
#include <vector>
#pragma GCC diagnostic ignored "-Wmisleading-indentation"
#pragma GCC diagnostic ignored "-Wsign-compare"
#include "InfInt.h"
#include "CLI11.hpp"
#include "calc_factors.h"
#include <future>


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
    vector<future<vector<InfInt>> > factorFutures{};

    CLI::App app("Factor numbers");
    app.add_option("number", input, "numbers to factor")->required()->check(checkValidator);
    bool asy{false};
    app.add_flag("-a, --async", asy, "async");
    CLI11_PARSE(app, argc, argv);

    try {
        app.parse(argc, argv);
        vector<InfInt> newInput;

        for(int i = 0; i < input.size(); i++){
            InfInt input_item = input[i];
            newInput.push_back(input_item);
        }

        for (const InfInt& number : newInput) {
            factorFutures.push_back(async(launch::async, get_factors, number));
        }

        int index = 0;
        while (!factorFutures.empty()) {
            auto factorFuture = factorFutures.begin();

            if (factorFuture->wait_for(chrono::milliseconds(1000)) == future_status::ready) {
                vector<InfInt> factors = factorFuture->get();

                cout << newInput[index++] << ": ";
                for (const InfInt& factor : factors) {
                    cout << factor << " ";
                }
                cout << endl;
                factorFutures.erase(factorFuture);
            }
        }
    } catch (const CLI::ParseError &error){
        return app.exit(error);
    }
}