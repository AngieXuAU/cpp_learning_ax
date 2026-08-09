# C++ File IO and String Manipulation

## File and String Manipulation

#### 🧠 Active Recall Questions
1. **Memory & Performance:** What are the syntactic and runtime allocation differences between `std::stringstream` and `std::views::split`?
2. **Mechanics of `getline`:** Walk through the exact memory copy and allocation steps when executing `std::getline(ss, token, ',')`.
3. **Buffer Reuse Pattern:** How does defining the target token string *outside* the `std::getline` loop optimize performance, and what C++ mechanisms are at play?
4. **Lazy Evaluation:** What does `std::views::split` lazily return under the hood, and how does the compiler extend its lifetime during a range-based `for` loop?
5. **Subrange Conversion:** Why is constructing a `std::string_view` from a subrange a zero-allocation operation, and what are its time/space complexities?
6. **Edge Cases:** How does `std::getline` handle consecutive delimiters (e.g. `a,,b`), and what value is produced?
7. **Zero-Allocation Numeric Parsing:** How do you parse an integer from a `std::string_view` without allocating a temporary `std::string`?

Answers:
1. `std::stringstream` uses stream-extraction syntax and copies input into a heap-allocated buffer, while `std::views::split` uses a pipeline operator (`|`) to return non-owning subranges lazily with zero heap allocations.
2. `std::getline` scans the stream from the current read pointer up to the delimiter, clears the destination string using `.clear()` (retaining its capacity), copies the characters, and only allocates new heap memory if the token size exceeds the string's current capacity.
3. Defining the target string outside the loop keeps the same string object alive, allowing `std::getline`'s internal `.clear()` call to preserve and reuse the already allocated memory buffer, bypassing heap churn.
4. `std::views::split` returns a temporary range adapter view containing iterators, and the compiler desugars the range-based `for` loop to bind this temporary view to a hidden reference (`auto&&`), extending its lifetime for the duration of the loop.
5. It is a zero-allocation operation because the `std::string_view` constructor only copies a pointer and a length from the subrange to the stack, yielding $O(1)$ time and space complexity.
6. `std::getline` treats consecutive delimiters as enclosing an empty field, returning an empty string `""` for that segment.
7. Use `std::from_chars` (from `<charconv>`), which takes a raw character pointer range and parses directly from the underlying buffer, returning a status struct rather than throwing exceptions.

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
  * `stringstream` copies the input string into an internal heap buffer (`std::stringbuf`) and maintains an internal **read pointer** (cursor) to track the current parsing position.
  * `getline` scans characters from the current read pointer until it encounters the delimiter. It then:
    1. Calls `token.clear()`, which resets the string's size to 0 but **retains its allocated capacity** (preventing deallocation).
    2. Copies the extracted token into `token`'s existing buffer. A new heap allocation only occurs if the token's length exceeds the string's current capacity.
    3. Advances the stream's read pointer past the delimiter.

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
* **Zero-Allocation Numbers (`std::from_chars`):** Standard conversion functions like `std::stoi` only accept `std::string`, forcing a heap allocation when given a `std::string_view`. Use `std::from_chars` from `<charconv>` to parse directly from the slice pointers.

---

## Low-Level Layout of Strings and Views

#### 🧠 Active Recall Questions
1. **Internal Layout:** What two fields define the internal layout of `std::string_view`, and how many bytes does it occupy on a 64-bit platform?
2. **Ownership & Safety:** Explain the concept of ownership in `std::string_view`. How does a dangling pointer/reference occur with it, and what happens at runtime?
3. **Explicit Constructors:** Why does `std::string s = my_string_view;` fail to compile? What is the correct syntax to construct the string, and what happens in memory during this operation?
4. **SSO Mechanics:** Describe the memory layout of `std::string` for large strings versus small strings (SSO). What metadata is stored on the stack, and when is heap memory allocated?
5. **Iterator Abstraction:** Under the hood, what is an iterator for contiguous containers (`std::string`, `std::vector`), and how does incrementing (`it++`) translate at the assembly/hardware level?
6. **Iterator Out-of-Bounds:** What happens physically and compiler-wise when you increment or dereference a split view iterator past its end?

Answers:
1. `std::string_view` is defined by a `const char* ptr` pointing to the character data and a `size_t length` representing the size, occupying 16 bytes on a 64-bit platform.
2. `std::string_view` is non-owning, meaning it points to memory owned by another container, and if that container is destroyed or resized, the view becomes a dangling pointer, leading to undefined behavior at runtime.
3. It fails to compile because the `std::string` constructor taking `std::string_view` is marked `explicit`; the correct syntax is direct-initialization (`std::string s{my_string_view}`), which performs a heap allocation to copy the characters.
4. For large strings, `std::string` stores a pointer, size, and capacity on the stack while allocating the data on the heap, but for small strings (typically < 15–23 characters), it bypasses heap allocation by storing data directly in an internal stack buffer (SSO).
5. An iterator for contiguous containers is a raw pointer (or a thin wrapper around one), and incrementing it translates to a single assembly instruction offsetting the pointer based on the size of the elements.
6. Physically, it may read adjacent stack/heap memory or default-sentinel memory (often resolving safely as an empty string in debug/unoptimized runs), but compiler-wise it is Undefined Behavior (UB) and under optimization (`-O3`) can result in register/memory corruption or aggressive deletion of code paths.

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
* **Contiguous Iterators:** For contiguous containers (`std::string`, `std::string_view`, `std::vector`), an iterator under the hood is simply a raw pointer (or a thin wrapper behaving exactly like one). Incrementing (`it++`) offsets the pointer by the element size.
* **End-Iterator Safety:** Dereferencing an iterator that has reached `end()` is **Undefined Behavior**.
  * *Debug/Unoptimized:* May return an empty subrange pointing to the string's null-terminator (no immediate OS crash).
  * *Optimized (`-O3`):* The compiler assumes UB never happens, potentially optimizing away critical conditional code, leading to silent data corruption, register mismatch, or random segfaults. Always check `it != view.end()` before dereferencing or incrementing.
