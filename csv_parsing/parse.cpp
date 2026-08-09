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
        auto end = split_view.end();

        // safely access the next column
        auto get_next_col = [&it, end]() -> std::string_view {
            if (it == end) return {};  // return empty if we get to the end

            std::string_view val(*it);
            ++it;
            return val;
        };

        // title
        std::string_view title_sv = get_next_col();

        // author
        std::string_view author_sv = get_next_col();

        // year
        std::string_view year_sv = get_next_col();
        int year = 0;
        std::from_chars(year_sv.data(), year_sv.data() + year_sv.size(), year);

        // pages
        std::string_view pages_sv = get_next_col();
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