
#include<iostream>
#include<vector>
#include<algorithm>

int main(){
    const int count = 5;
    int temp = 0;

    std::vector<int> given;

    std::cout << "This program returns the second largest unique integer entered. Enter five integers, each followed by a new line: ";

    for (int i = 0; i < count; i++) {
        if ( !(std::cin >> temp) ){
            std::cout << "Invalid input. Enter an integer." << std::endl;
            continue;
        }

        else if (std::find(given.begin(), given.end(), temp) == given.end()){
            given.push_back(temp);
        }

    }

    std::sort(given.begin(), given.end());

    if (given.size() >= 2) {
        given.pop_back();
        std::cout << "The second largest number is " << given.back() << std::endl;
    } else {
        std::cout << "There are not enough numbers to determine a second largest." << std::endl;
    }

    return 0;
}