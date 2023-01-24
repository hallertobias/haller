#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "asio.hpp"

using namespace std;
using namespace asio::ip;

int main() { 
    asio::io_context ctx;
    tcp::endpoint ep{tcp::v4(), 1113};
    tcp::acceptor acceptor{ctx, ep}; 
    acceptor.listen();
    tcp::socket sock{ctx};
    acceptor.accept(sock);
    tcp::iostream strm{move(sock)};
    string data;
    strm >> data; 
    strm << data;
    strm.close(); 
}