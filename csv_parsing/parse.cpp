// defines a Book struct, opens books.csv, parses the data, loads them into a
// vector, and prints the title of each book that has more than 300 pages

#include <fstream>
#include <iostream>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>

struct Book {
    std::string name;
    std::string author;
    int yearPublished;
    int pages;
};

int main() {
    std::ifstream data("data.csv");

    if (!data.is_open()) {
        std::cerr << "Error: could not open file.\n";
        return 1;
    }

    std::vector<std::string> books;

    std::string line;
    std::getline(data, line);  // discard the header
    while (std::getline(data, line)) {
        // printing the line
        if (line == "") {
            continue;
        }

        // read the line
        std::cout << "Read line: " << line << "\n";

        // split the line
        for (auto sub : line | std::views::split(',')) {
            std::string val((std::string_view(sub)));
        }
    }
    return 0;
}