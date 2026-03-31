
#include <iostream>

using namespace std;

int main(){
    int interval;

    cout << "This program prints all the multiples of a certain number up to 50.\n Enter the interval wanted: ";
    cin >> interval;

    for(int i = interval; i <= 50; i += interval){
        cout << i << "\t";
    }
}