Here are **3 basic coding exercises** designed to build the exact skills you need to achieve **Stage 1 (CSV parsing)**. You can copy these instructions and template codes into a separate workspace or folder to practice.

---

### The Goal of Stage 1
You need to define a `Point` struct that represents a row in the CSV, read a CSV file line-by-line, parse each comma-separated value, populate your `Point` struct, and store it in a dynamic array (`std::vector<Point>`).

---

### Step 0: Create a Practice CSV
In your separate workspace, create a file named `test.csv` with the following contents:
```csv
match_id,PointNumber,PointWinner,PointServer,P1Score,P2Score
ausopen_2024_final,1,1,1,15,0
ausopen_2024_final,2,1,1,30,0
ausopen_2024_final,3,2,1,30,15
```

---

### Exercise 1: Structs and Vectors
**Goal:** Learn how to group variables using a `struct` and store objects in a dynamic array (`std::vector`).

```cpp
#include <iostream>
#include <string>
#include <vector>

// 1. Define a struct named 'Point' to hold:
//    - match_id (string)
//    - point_number (int)
//    - p1_score (string) - (Scores can be "15", "30", "game", "Ad", so string is best)
struct Point {
    std::string match_id;
    int point_number;
    std::string p1_score;
};

int main() {
    // 2. Declare a vector of Point structs
    std::vector<Point> points;

    // 3. Create a point and add it
    Point p1;
    p1.match_id = "ausopen_24";
    p1.point_number = 1;
    p1.p1_score = "15";
    points.push_back(p1);

    // 4. Create another point using uniform initialization
    Point p2{"ausopen_24", 2, "30"};
    points.push_back(p2);

    // 5. Print the vector using a range-based loop
    for (const Point& p : points) {
        std::cout << "Point #" << p.point_number << " Score: " << p.p1_score << "\n";
    }
    return 0;
}
```

---

### Exercise 2: File I/O (Reading Line-by-Line)
**Goal:** Learn how to safely open a file and read it line-by-line using `std::ifstream` and `std::getline`.

```cpp
#include <iostream>
#include <fstream>
#include <string>

int main() {
    // 1. Open the file
    std::ifstream file("test.csv");

    // 2. Safety check: did it open successfully?
    if (!file.is_open()) {
        std::cerr << "Failed to open file!\n";
        return 1;
    }

    std::string line;
    // 3. Read line-by-line until end of file
    while (std::getline(file, line)) {
        std::cout << "Line: " << line << "\n";
    }

    // 4. Close the file stream
    file.close();
    return 0;
}
```

---

### Exercise 3: CSV Parsing with `std::stringstream`
**Goal:** Split each comma-separated line into individual fields, convert numbers using `std::stoi`, and populate the struct.

```cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

struct Point {
    std::string match_id;
    int point_number;
    int winner;
    int server;
    std::string p1_score;
    std::string p2_score;
};

int main() {
    std::ifstream file("test.csv");
    if (!file.is_open()) return 1;

    std::vector<Point> points;
    std::string line;

    // 1. Read and discard the header row
    std::getline(file, line);

    // 2. Parse data rows
    while (std::getline(file, line)) {
        if (line.empty()) continue; // skip blank lines

        // std::stringstream lets us treat a string like an input stream
        std::stringstream ss(line);
        std::string cell;
        Point p;

        // Column 1: match_id (string)
        std::getline(ss, p.match_id, ',');

        // Column 2: PointNumber (int)
        std::getline(ss, cell, ',');
        p.point_number = std::stoi(cell); // converts string "1" to integer 1

        // Column 3: PointWinner (int)
        std::getline(ss, cell, ',');
        p.winner = std::stoi(cell);

        // Column 4: PointServer (int)
        std::getline(ss, cell, ',');
        p.server = std::stoi(cell);

        // Column 5: P1Score (string)
        std::getline(ss, p.p1_score, ',');

        // Column 6: P2Score (string)
        std::getline(ss, p.p2_score, ',');

        points.push_back(p);
    }
    file.close();

    // Verify by printing
    for (const Point& p : points) {
        std::cout << "Parsed point " << p.point_number << " | Score: " << p.p1_score << "-" << p.p2_score << "\n";
    }
    return 0;
}
```

---

### How to Compile in your terminal:
```powershell
g++ -std=c++17 main.cpp -o main
./main
```

Let me know once you have practiced these and are ready to map out the actual Stage 1 implementation inside this workspace!