
#include <iostream>
#include <string>           // add this to guarantee it works on everything

using namespace std;

int main(){
    string user_in;
    int vowels = 0;

    // take input
    cout << "This program counts how many vowels appear in a string. Enter a string: ";
    getline(cin, user_in);

    // loop through the string
    for(char c_raw: user_in){
        char c = tolower(c_raw);
        
        if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'){
            vowels ++;           
        }
    }

    // print the result
    cout << "There are " << vowels << " vowels. ";

    return 0;
}