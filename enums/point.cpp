#include <iostream>

enum class PointOutcome {
    Ace,
    // Winner,
    UFE,
    // ForcedError,
    Routine
};

PointOutcome parse_outcome(bool is_ace, bool is_ufe) {
    if (is_ace) {
        return PointOutcome::Ace;
    } else if (is_ufe) {
        return PointOutcome::UFE;
    } else {
        return PointOutcome::Routine;
    }
}

std::string outcome_to_string(PointOutcome outcome) {
    switch (outcome) {
        case PointOutcome::Ace:
            return "Ace";
        // case PointOutcome::Winner:
        //     return "Winner";
        case PointOutcome::UFE:
            return "Unforced Error";
        // case PointOutcome::ForcedError:
        //     return "Forced Error";
        case PointOutcome::Routine:
            return "Routine";
    }
    return "Unknown";
}

int main() {
    std::string result1, result2, result3;
    result1 = outcome_to_string(parse_outcome(1, 0));
    result2 = outcome_to_string(parse_outcome(0, 1));
    result3 = outcome_to_string(parse_outcome(0, 0));

    std::cout << result1 << "\n";
    std::cout << result2 << "\n";
    std::cout << result3 << "\n";
    return 0;
}