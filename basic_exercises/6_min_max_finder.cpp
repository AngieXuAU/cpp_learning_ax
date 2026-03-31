
#include <iostream>
#include <vector>

using namespace std;

int main(){
    const int count = 5;
    vector<float> nums(count);

    cout << "This program returns the smallest and largest of five numbers. Enter five numbers: ";
    for(float &val : nums){                         // take input. Note the proper **range-based syntax for input**
        if(!(cin >> val)){
            cout << "Invalid input, please enter a number!";
            return 1;
        }
    }

    float largest = nums[0];
    float smallest = nums[0];              // start by assigning the first number to both largest and smallest

    for(int i=1; i < 5; i++){                       // loop through the list
        if(nums[i] > largest){                      // assign to largest if > largest
            largest = nums[i];
        } else if(nums[i] < smallest){              // assign to smallest if < smallest
            smallest = nums[i];
        }
    }

    cout << "Largest: " << largest << "\nSmallest: " << smallest << endl;
}