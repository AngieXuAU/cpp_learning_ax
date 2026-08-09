Viewed point.hpp

Here is your staged **Learning Roadmap for C++ `enum class`**. 

Completing these 4 progressive exercises will give you all the foundational skills needed to use enums for your tennis project.

---

### Prerequisites & Dependencies Checklist

Before using enums in your project, you should be comfortable with:
- [ ] Defining an `enum class` in C++
- [ ] Comparing enum values using `==` and `!=`
- [ ] Using `switch` statements with an enum
- [ ] Writing a helper function to convert an `enum class` to a printable `std::string`
- [ ] Converting raw inputs (numbers or booleans) into an `enum class` value

---

### Progressive Learning Stages & Practice Exercises

#### Stage 1: Definition & Basic Assignment
* **Concept**: An `enum class` (scoped enum) creates a brand-new custom type containing a fixed list of named constants.

* **Syntax Preview**:
  ```cpp
  enum class TrafficLight {
      Red,
      Yellow,
      Green
  };
  ```

* **Practice Task 1**:
  Define an `enum class Season` with four values: `Spring`, `Summer`, `Autumn`, `Winter`. Declare a variable of type `Season` and assign it to `Season::Summer`.

---

#### Stage 2: Control Flow with `switch` Statements
* **Concept**: `switch` statements pair naturally with `enum class`. The compiler will warn you if you forget to handle one of the enum values!

* **Practice Task 2**:
  Write a small function `std::string get_action(TrafficLight light)` that uses a `switch` statement to return:
  - `"Stop"` for `TrafficLight::Red`
  - `"Caution"` for `TrafficLight::Yellow`
  - `"Go"` for `TrafficLight::Green`

---

#### Stage 3: Converting Enum to Printable String (Display Helper)
* **Concept**: Unlike `int` or `std::string`, you cannot directly do `std::cout << light`. You must write a helper function to turn the enum into a human-readable string for display.

* **Practice Task 3**:
  Define a `PointOutcome` enum class with values: `Ace`, `Winner`, `UnforcedError`, `ForcedError`, `Routine`.
  Write a function `std::string outcome_to_string(PointOutcome outcome)` that returns the matching string representation.

---

#### Stage 4: Parsing Raw Data into Enum Values (CSV Ingestion Helper)
* **Concept**: In real projects, external data comes as raw numbers/booleans (e.g., from CSV columns `is_ace`, `is_unforced_error`). You write a converter function to map raw values into your clean `enum class`.

* **Practice Task 4**:
  Suppose you have two boolean inputs from a CSV row: `bool is_ace` and `bool is_unforced_error`.
  Write a function `PointOutcome parse_outcome(bool is_ace, bool is_unforced_error)` that returns:
  - `PointOutcome::Ace` if `is_ace` is true
  - `PointOutcome::UnforcedError` if `is_unforced_error` is true
  - `PointOutcome::Routine` otherwise.

---
