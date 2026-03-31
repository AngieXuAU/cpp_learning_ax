
#include <iostream>
#include <vector>


int main(){

    int total = 0;
    const int count = 5;                // 5 user inputs taken
    std::vector<int> user_in(count);

    std::cout << "This program stores 5 user input integers in a vector and returns the vector and their sum. Enter 5 integers: ";

    for(int i = 0; i < count; i++){     // looping from 0 to 4
        if(!(std::cin >> user_in[i])){  // check input validity
            std::cout << "Please enter integers only!";
            return 1;
        } 
        
        total += user_in[i];
    }

    for(int j: user_in){
        std::cout << j << "\t";         // print out vector
    }

    std::cout << "\nTotal: " << total;

    return 0;
}