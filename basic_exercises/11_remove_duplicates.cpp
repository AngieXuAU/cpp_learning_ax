
#include<iostream>
#include<vector>
#include<algorithm>

int main(){
    const int count = 5;
    int temp = 0;

    std::vector<int> given;

    std::cout << "This program removes duplicates from a given vector. Input a list of five integers: ";

    for (int i = 0; i < count; i++) {
        if ( !(std::cin >> temp) ){
            std::cout << "Input is not valid. Enter an integer.";
            return 0;
        }

        else if (std::find(given.begin(), given.end(), temp) == given.end()){
            given.push_back(temp);
        }

    }

    for (int num: given){
        std::cout << num << "\t";
    }

    std::cout << std::endl;

    return 0;
}