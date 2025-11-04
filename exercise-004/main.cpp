#include <fmt/chrono.h>
#include <fmt/format.h>
#include <cmath>

#include "CLI/CLI.hpp"
#include "config.h"

class Point {
private:
    int x;
    int y;

public:
    // Standardkonstruktor: setzt x und y auf 0
    Point() : x(0), y(0) {}

    // Konstruktor mit Parametern
    Point(int x_val, int y_val) : x(x_val), y(y_val) {}

    // Methode zum Verschieben des Punktes
    void move(int dx, int dy) {
        x += dx;
        y += dy;
    }

    // Ausgabe der Koordinaten
    void print() const {
        fmt::print("({}, {})\n", x, y);
    }

    // Zusatzaufgabe: Abstand zu einem anderen Punkt berechnen
    double distance_to(const Point& other) const {
        int dx = x - other.x;
        int dy = y - other.y;
        return std::sqrt(dx * dx + dy * dy);
    }
};

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
    Point p1(2, 3);     // Erzeugen eines Punktes (2, 3)
    p1.print();         // Ausgabe: (2, 3)

    p1.move(1, -1);     // Verschiebe um (1, -1)
    p1.print();         // Ausgabe: (3, 2)

    Point p2;           // Standardkonstruktor -> (0, 0)
    p2.print();         // Ausgabe: (0, 0)

    // Zusatz: Abstand berechnen
    double dist = p1.distance_to(p2);
    fmt::print("Abstand zwischen p1 und p2: {}\n", dist);
    return 0; /* exit gracefully*/
}
