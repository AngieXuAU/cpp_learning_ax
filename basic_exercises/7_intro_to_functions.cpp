
#include <iostream>

using namespace std;

int larger(float a, float b){
    
    // original: using if conditionals
    
    // if(b > a){
    //     return b;
    // }
    // return a;

    // alternate: ternary / conditional operator

    return (b > a)? b : a;
}

int main(){
    float x = 0, y = 0;

    cout << "This program returns the higher of two integer inputs. Enter the first integer: ";
    if(!(cin >> x)){
        cout << "Invalid input, please enter a number!";
        return 1;
    }

    cout << "Enter the second integer: ";
    if(!(cin >> y)){
        cout << "Invalid input, please enter a number!";
        return 1;
    }

    cout << larger(x, y);

    return 0;
}