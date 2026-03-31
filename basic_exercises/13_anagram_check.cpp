
#include <iostream>
#include <string>
#include <map>
#include <set>

int main(){
    std::set<char> seen = {};

    std::string str1 = "", str2 = "";

    std::cout << "This program determines wwhether two strings are anagrams. Enter the first string: ";     // take input
    std::getline(std::cin, str1);
    std::cout << "Enter the second string: ";
    std::getline(std::cin, str2);

    std::map<char, int> comparison;                                                                         // map created for comparison


    if(str1.length() != str2.length()){         // if the length is different they are not anagrams
        std:: cout << false;
        return 0;
    }

    for(char c: str1){                          // loop through string 1
        if(seen.find(c) == seen.end()){         // if the character is not already in the seen set
            comparison[c] = 1;                  // set the character as a key and the value to be 1
            seen.insert(c);                     // add it to the "seen" set
        } else {
            comparison.at(c) ++;                // if the character is in the seen set, add 1 to its value
        }                    
    }

    // for(char index: seen){
    //     std::cout << index << "\t";
    // }

    for(char c2: str2){
        if(seen.find(c2) == seen.end() || comparison.at(c2) == 0){                        // if the character is not already in the seen set, it can't be an anagram
            std:: cout << false;
            return 0;
        } else {
            comparison.at(c2) --;
        }
    }

    std::cout << true;
    return 0;

    // NB: use [] operator for more conciseness
}