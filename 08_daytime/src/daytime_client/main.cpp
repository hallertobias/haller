#include "spdlog/spdlog.h"
#include "asio.hpp"
#include <iostream>

using namespace std;
using namespace asio::ip;

int main() {
    tcp::iostream stream("localhost", "1113");

    if (stream) {
        string line;
        getline(stream, line);
        cout << line << endl;
    } else {
        spdlog::error("No connection to the server");
    }
}