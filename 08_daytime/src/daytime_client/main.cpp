#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "asio.hpp"
#include <iostream>

using namespace std;
using namespace asio::ip;

int main() {
    auto logger = spdlog::stderr_color_mt("blue");

    tcp::iostream stream("localhost", "1113");

    if (stream) {
        string line;
        getline(stream, line);
        logger->info(line);
        cout << line << endl;
    } else {
        cout << "No connection to the server" << endl;
    }
}