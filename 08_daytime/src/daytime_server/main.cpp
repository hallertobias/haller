#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "asio.hpp"
#include <chrono>
#include "CLI11.hpp"
#include "timeutils.h"

using namespace std;
using namespace asio::ip;

int main(int argc, char* argv[]) { 
    spdlog::info("Server started");

    CLI::App app{"Daytime Server"};
    unsigned short port = 1113;
    app.add_option("-p, --port", port, "server port");

    CLI11_PARSE(app, argc, argv);

    asio::io_context ctx;
    tcp::endpoint ep{tcp::v4(), port};
    tcp::acceptor acceptor{ctx, ep}; 
    acceptor.listen();
    tcp::socket sock{ctx};
    while(true) {
        acceptor.accept(sock);
        tcp::iostream strm{move(sock)};
        if(strm) {
            try {
                strm << chrono::system_clock::now() << endl;
            } catch(...) {
                spdlog::error("Could not send correctly");
            }
        } else {
            spdlog::error("Could not connect to client");
        }
        strm.close(); 
    }
}