#include "spdlog/spdlog.h"
#include "asio.hpp"
#include <iostream>
#include "CLI11.hpp"

using namespace std;
using namespace asio::ip;

int main(int argc, char* argv[]) {
    CLI::App app{"Daytime Client"};

    unsigned short port = 1113;
    app.add_option("-p, --port", port, "port to connect to");

    CLI11_PARSE(app, argc, argv);

    tcp::iostream stream("localhost", to_string(port));

    if (stream) {
        string line;
        getline(stream, line);
        cout << line << endl;
    } else {
        spdlog::error("Could not connect to server");
    }
}