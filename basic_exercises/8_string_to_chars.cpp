
#include <iostream>
#include <string>

using namespace std;

int main(){
    string user_in;
    
    cout << "This program tells you the length of a string and prints out each character on a new line. Enter a string: ";
    cin >> user_in; // original
    getline(cin, user_in);

    cout << "The length is " << user_in.length() << ".";

    // for(size_t i = 0; i < user_in.length(); i++){                original
    //     cout << "\n" << user_in[i];
    // }

    for (char c: user_in){
        cout << "\n" << c;
    }

    return 0;
}