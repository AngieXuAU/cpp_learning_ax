
enum class Season { Spring, Summer, Autumn, Winter };

int main() {
    Season season = Season::Summer;
    Season prior_season = static_cast<Season>(0);
    return 0;
}