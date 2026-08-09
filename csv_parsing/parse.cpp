// defines a Book struct, opens books.csv, parses the data, loads them into a
// vector, and prints the title of each book that has more than 300 pages

#include <charconv>
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

    std::vector<Book> books;
    std::string line;
    std::getline(data, line);  // discard the header

    while (std::getline(data, line)) {
        // skip empty lines
        if (line.empty()) {
            continue;
        }

        // // printing the line
        // std::cout << "Read line: " << line << "\n";

        auto split_view = line | std::views::split(',');
        auto it = split_view.begin();
        // auto end = split_view.end();

        // title
        std::string_view title_sv(*it);

        // author
        ++it;
        std::string_view author_sv(*it);

        // year
        ++it;
        std::string_view year_sv(*it);
        int year = 0;
        std::from_chars(year_sv.data(), year_sv.data() + year_sv.size(), year);

        // pages
        ++it;
        std::string_view pages_sv(*it);
        int pages = 0;
        std::from_chars(pages_sv.data(), pages_sv.data() + pages_sv.size(), pages);

        books.push_back(Book{std::string(title_sv), std::string(author_sv), year, pages});
    }
    for (const auto& book : books) {
        std::cout << book.name << " has " << book.pages << " pages.\n";
        // if (book.pages > 300) {
        // }
    }
    return 0;
}