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
#include <thread>


using namespace std;

string checkValidator(const string& s){
    size_t found = s.find_first_not_of("0123456789");
    if (found != string::npos){
         throw CLI::ValidationError(s +" contains not numeric character");
    }else{
        return ""; 
    }
}

void printFactors(vector<shared_future<vector<InfInt>>>& factorFutures, vector<InfInt>& numbers) {
    for(int i=0; i < factorFutures.size(); i++) {
        shared_future<vector<InfInt>>& factorFuture = factorFutures.at(i);
        if (factorFuture.wait_for(chrono::milliseconds(1000)) == future_status::ready) {
            vector<InfInt> factors = factorFuture.get();
            cout << numbers[i] << ": ";
            for (const InfInt& factor : factors) {
                cout << factor << " ";
            }
            cout << endl;
        }
    }
}

void checkFactors(vector<shared_future<vector<InfInt>>>& factorFutures, vector<InfInt>& numbers) {
    for(int i=0; i < factorFutures.size(); i++) {
        shared_future<vector<InfInt>>& factorFuture = factorFutures.at(i);
        if (factorFuture.wait_for(chrono::milliseconds(1000)) == future_status::ready) {
            vector<InfInt> factors = factorFuture.get();
            InfInt checksum = 1;
            for(const InfInt& factor : factors) {
                checksum *= factor;
            }
            if(checksum != numbers[i]) {
                cerr << "ERROR: " << numbers[i] << " not the right product" << endl;
            }
        }
    }
}

int main(int argc, char* const argv[]) {
    vector<string> input;
    vector<shared_future<vector<InfInt>> > factorFutures{};

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

        thread printThread{printFactors, ref(factorFutures), ref(newInput)};
        printThread.join();
        thread checkThread{checkFactors, ref(factorFutures), ref(newInput)};
        checkThread.join();
    } catch (const CLI::ParseError &error){
        return app.exit(error);
    }
}