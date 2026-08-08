# C++

## File and String Manipulation

#### 🧠 Active Recall Questions
* **Memory & Performance:** What are the syntactic and runtime allocation differences between `std::stringstream` and `std::views::split`?
* **Mechanics of `getline`:** Walk through the exact memory copy and allocation steps when executing `std::getline(ss, token, ',')`.
* **Buffer Reuse Pattern:** How does defining the target token string *outside* the `std::getline` loop optimize performance, and what C++ mechanisms are at play?
* **Lazy Evaluation:** What does `std::views::split` lazily return under the hood, and how does the compiler extend its lifetime during a range-based `for` loop?
* **Subrange Conversion:** Why is constructing a `std::string_view` from a subrange a zero-allocation operation, and what are its time/space complexities?
* **Edge Cases:** How does `std::getline` handle consecutive delimiters (e.g. `a,,b`), and what value is produced?

### String Splitting Options

| Method | Syntax | Allocations | Notes |
| :--- | :--- | :--- | :--- |
| **`stringstream`** | `stringstream ss(line); getline(ss, tok, ',');` | High (copies input + allocs tokens) | Easy, std, handles empty fields |
| **`views::split`** (C++20) | `line \| views::split(',')` | Zero (views point to original memory) | Fast, no copy, returns subranges |

### Bare Bones Implementation Examples

#### 1. Stream-based (traditional)
```cpp
#include <sstream>
#include <string>
#include <iostream>

void split_stream(const std::string& line) {
    std::stringstream ss(line);
    std::string token; // Declare outside to reuse buffer (avoid heap churn)
    while (std::getline(ss, token, ',')) {
        std::cout << token << "\n";
    }
}
```
* **Mechanics:**
  * `stringstream` copies the input string into an internal heap buffer (`std::stringbuf`) and sets a read pointer.
  * `getline` scans characters from the read pointer until the delimiter, copies them into `token` (triggering heap allocation if token exceeds SSO), and advances the pointer.

#### 2. Range-based Pipeline (C++20/23)
```cpp
#include <ranges>
#include <string_view>
#include <iostream>

void split_range(std::string_view line) {
    for (auto sub : line | std::views::split(',')) {
        // Construct string_view from subrange (no allocations)
        std::cout << std::string_view(sub) << "\n";
    }
}
```
* **Mechanics:**
  * `views::split` splits lazily. It returns a temporary View object containing iterators over the original memory buffer (no copy or immediate split).
  * In a range `for` loop, the compiler desugars the loop by binding the temporary view to a hidden reference (`auto&& __range`), extending its lifetime for the loop.
  * You can manually store the view if needed (e.g., `auto my_view = line | std::views::split(',')`).
  * `std::string_view(sub)` constructs a stack-based pointer + length wrapper ($O(1)$ time/space, zero heap allocations).

### Key Low-Level Takeaways
* **SSO (Small String Optimization):** Strings < 15-23 chars stay on stack. Larger strings allocate on heap.
* **Buffer Reuse:** Define `std::string` target *outside* loop when using `getline` to reuse buffer capacity & eliminate heap allocations.
* **Consecutive Delimiters:** `getline` returns empty string `""` for consecutive delimiters (e.g. `a,,b` $\rightarrow$ `a`, `""`, `b`).

### Low-Level Layout of Strings and Views

#### 🧠 Active Recall Questions
* **Internal Layout:** What two fields define the internal layout of `std::string_view`, and how many bytes does it occupy on a 64-bit platform?
* **Ownership & Safety:** Explain the concept of ownership in `std::string_view`. How does a dangling pointer/reference occur with it, and what happens at runtime?
* **Explicit Constructors:** Why does `std::string s = my_string_view;` fail to compile? What is the correct syntax to construct the string, and what happens in memory during this operation?
* **SSO Mechanics:** Describe the memory layout of `std::string` for large strings versus small strings (SSO). What metadata is stored on the stack, and when is heap memory allocated?
* **Iterator Abstraction:** Under the hood, what is an iterator for contiguous containers (`std::string`, `std::vector`), and how does incrementing (`it++`) translate at the assembly/hardware level?

#### 1. `std::string_view` (C++17)
* **Under the hood:** A struct containing exactly two fields:
  * `const char* ptr`: Points to the start of the character sequence.
  * `size_t length`: Number of characters in the view.
* **Size:** 16 bytes (on 64-bit platforms).
* **Ownership:** Non-owning. Crucial to watch out for **dangling pointers** if the owning container (like `std::string`) goes out of scope or is modified.
* **Initialization:** Converting `std::string_view` to `std::string` requires **direct-initialization** (e.g., `std::string s{view}`) because the `std::string` constructor is `explicit`.

#### 2. `std::string`
* **Under the hood (Stack vs. Heap):**
  * **Large Strings:** The stack object (typically 32 bytes) holds metadata (`char* data_ptr`, `size_t size`, `size_t capacity`). The actual data lives in the heap.
  * **Small String Optimization (SSO):** If string length is small (typically $< 15$ or $23$ chars depending on compiler), the characters are stored directly within the stack object's union buffer, bypassing heap allocation entirely.

#### 3. Iterators
* For contiguous containers (`std::string`, `std::string_view`, `std::vector`), an iterator under the hood is simply a raw pointer (or a thin wrapper behaving exactly like one). Incrementing (`it++`) offsets the pointer by the element size.