# Enums

## Active Recall Questions

1. Why does C++ prevent implicit conversions between integers and `enum class`?
2. Why is a fallback return statement required at the end of a non-void function that switches on an enum?
3. How can you customize the underlying storage size of an `enum class` to save memory?
4. What is the consequence of performing `static_cast` to cast an out-of-range integer to an enum type?
5. How do bitmask enums represent values not explicitly declared in the definition?

### Answers:
1. To enforce type safety, preventing invalid state assignments and accidental comparisons of unrelated enum types.
2. Because dynamic inputs or explicit casts can pass values not covered by any switch case, bypassing the block and causing Undefined Behavior if no return exists.
3. Use colon syntax after the enum name to specify the underlying integer type (e.g., `: std::uint8_t`).
4. It compiles successfully without runtime checks to avoid overhead, but stores the raw out-of-range integer value in the enum variable.
5. They use power-of-two enumerators to set individual bits, which can be combined using bitwise OR to represent composite states.

---

## Technical Reference

### Scoped Enums (`enum class`)
- Introduced in C++11 to replace legacy C-style enums.
- **Syntax**: `enum class Name : UnderlyingType { Val1, Val2 };`
- Prevents name pollution: Values are scoped under `Name::Val1`.
- Prevents implicit conversions to/from integer types.

### Memory & Performance Optimization
- Default underlying storage type is `int` (typically 4 bytes).
- Can override underlying storage to optimize memory layout/cache efficiency:
  ```cpp
  // Size: 1 byte instead of 4
  enum class PointOutcome : std::uint8_t {
      Ace,
      Winner,
      UFE
  };
  ```

### Switch Statements & Exhaustiveness Checking
- Pair naturally with enums. Modern compilers issue warnings (`-Wswitch`) if an enum value is not handled and no `default` is present.
- **Undefined Behavior Avoidance**: Even if all enum cases are handled, compilers cannot prevent users from passing invalid values via explicit casts. Therefore, non-void functions must contain a fallback `return` outside the `switch`.
  ```cpp
  std::string get_name(PointOutcome outcome) {
      switch (outcome) {
          case PointOutcome::Ace: return "Ace";
          // ... other cases
      }
      return "Unknown"; // Essential fallback to prevent UB
  }
  ```

### Explicit Casts & Bitmasks
- **Explicit Casting**: Done using `static_cast<EnumType>(val)`. No runtime range-checking is inserted by the compiler (zero-overhead philosophy).
- **Custom Value Assignment (`=`)**: Explicitly sets the underlying integer value.
- **Bitmasks**: Power-of-two assignments enable bitwise operations. Combined values (e.g. `Read | Write`) do not need to be declared in the enum itself.
  ```cpp
  enum class Permission : uint8_t {
      None = 0,    // 000
      Read = 1,    // 001
      Write = 2,   // 010
      Execute = 4  // 100
  };
  ```
