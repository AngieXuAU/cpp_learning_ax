
#include <iostream>

using namespace std;


int main(){
    float num1, num2 = 0;

    // take input
    cout << "This program gives the sum, difference, product and quotient of any two numbers. Enter the first number: ";
    cin >> num1;
    cout << "Enter the second number: ";
    cin >> num2;

    // do operations
    cout << "Sum = " << num1 + num2 << "\nDifference = " << abs(num1 - num2) << "\nProduct = " << num1 * num2 << "\nQuotient = " << num1 / num2;
    
}