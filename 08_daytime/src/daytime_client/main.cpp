#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

int main() {
    auto logger = spdlog::stderr_color_mt("blue");
    logger->info("sjdjf");
}