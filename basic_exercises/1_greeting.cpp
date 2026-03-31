
#include <iostream>

std::string user_in;

int main(){
    std::cout << "What is your name? ";
    std::cin >> user_in;
    std::cout << "Hello " << user_in << ", I am learning C++!";
    
    return 0;
}