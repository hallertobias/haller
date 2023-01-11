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
    vector<shared_future<vector<InfInt>>> factorFutures;

    CLI::App app("Factor numbers");
    app.add_option("number", input, "numbers to factor")->required()->check(checkValidator);
    bool asy{false};
    app.add_flag("-a, --async", asy, "async");
    CLI11_PARSE(app, argc, argv);

    try {
        app.parse(argc, argv);
        vector<InfInt> newInput;

        auto start = chrono::system_clock::now();

        for(int i = 0; i < input.size(); i++){
            InfInt input_item = input[i];
            newInput.push_back(input_item);
        }

        for (const InfInt& number : newInput) {
            if (asy) {
                factorFutures.push_back(async(launch::async, get_factors, number));
            } else {
                factorFutures.push_back(async(launch::deferred, get_factors, number));
                factorFutures.back().wait();
            }
        }

        thread printThread{printFactors, ref(factorFutures), ref(newInput)};
        thread checkThread{checkFactors, ref(factorFutures), ref(newInput)};

        for(int i=0; i < factorFutures.size(); i++) {
            if (factorFutures[i].wait_for(chrono::milliseconds(1000)) == future_status::ready) {
                i++;
            }
        }
        auto duration = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now() - start);

        printThread.join();
        checkThread.join();

        cout << "Time elapsed used for facotring: " << duration.count() << "ms" << endl;

    } catch (const CLI::ParseError &error){
        return app.exit(error);
    }
}