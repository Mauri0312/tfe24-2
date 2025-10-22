#include <fmt/chrono.h>
#include <fmt/format.h>

#include "CLI/CLI.hpp"
#include "config.h"
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>

// Funktion zum Ausgeben eines Vektors
void print_vector(const std::vector<int>& vec) {
    fmt::print("Values: ");
    for (const auto& v : vec) {
        fmt::print("{} ", v);
    }
    fmt::print("\n");
}
auto main(int argc, char **argv) -> int
{
    /**
     * CLI11 is a command line parser to add command line options
     * More info at https://github.com/CLIUtils/CLI11#usage
     */
    CLI::App app{PROJECT_NAME};
    try
    {
        app.set_version_flag("-V,--version", fmt::format("{} {}", PROJECT_VER, PROJECT_BUILD_DATE));
        app.parse(argc, argv);
    }
    catch (const CLI::ParseError &e)
    {
        return app.exit(e);
    }

    /**
     * The {fmt} lib is a cross platform library for printing and formatting text
     * it is much more convenient than std::cout and printf
     * More info at https://fmt.dev/latest/api.html
     */
    fmt::print("Hello, {}!\n", app.get_name());

    /* INSERT YOUR CODE HERE */
    
    int count = 10000;
    app.add_option("-c,--count", count, "Number of random values (default: 20)");

    CLI11_PARSE(app, argc, argv);

    fmt::print("Count is: {}\n", count);

    
    // Zufallszahlengenerator vorbereiten
    std::random_device rd; // echte Zufallsquelle (sofern verfügbar)
    std::mt19937 gen(rd()); // Mersenne Twister Generator
    std::uniform_int_distribution<> dist(1, 100); // Werte von 1 bis 100

    // Vektor erzeugen und mit Zufallswerten füllen
    std::vector<int> values(count);
    for (auto& v : values) {
        v = dist(gen);
    }

    fmt::print("Random vector with {} elements created.\n", count);

    print_vector(values);

    auto start = std::chrono::system_clock::now();

    std::sort(values.begin(), values.end());

    auto end = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);


    fmt::print("Sorted values:\n");
    print_vector(values);
    fmt::print("Sorting took {} ms.\n", elapsed.count());

    return 0; /* exit gracefully*/
}
