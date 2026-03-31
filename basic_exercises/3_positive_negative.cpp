
#include <iostream>

using namespace std;


int main(){
    float x;

    cout << "This program determines whether a number is positive, negative or 0. Enter any number: ";
    cin >> x;

    if (x == 0){
        cout << x << " is zero.";
    } else if (x > 0){
        cout << x << " is positive.";
    } else {
        cout << x << " is negative.";
    }
}