
#include <iostream>
#include <string>

using namespace std;

int main(){
    string user_in;

    cout << "This program reverses any string input. Enter a string: ";
    getline(cin, user_in);

    for(int i = user_in.length() - 1; i >= 0 ; i--){
        cout << user_in[i];
    }

    cout << endl;
    return 0;
}