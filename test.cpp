
#include <iostream>
#include <string>

int main(){

    int counter = 0;

    for (int i = 0; i < 5; i++){
        counter += i;

        std::cout << "Counter is now: " << counter << std::endl;
    }

    return 0;
}