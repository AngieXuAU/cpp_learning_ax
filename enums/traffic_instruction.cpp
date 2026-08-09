#include <iostream>

enum class TrafficLight { Red, Yellow, Green };

std::string get_action(TrafficLight light) {
    switch (light) {
        case TrafficLight::Green:
            return "Go";
        case TrafficLight::Yellow:
            return "Caution";
        case TrafficLight::Red:
            return "Stop";
    }
    return "Unknown";
}

int main() {
    std::cout << get_action(TrafficLight::Red) << "\n";
    return 0;
}