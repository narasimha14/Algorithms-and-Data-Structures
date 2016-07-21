/*
  @author: Narasimha Murthy
  Problem Link: https://www.hackerrank.com/challenges/palindrome-index

  Algorithm:
    Check the first and last index of the string until they are not equal, removing either one of the characters should result in a palindrome because of the problem specification.
    If it is already a palindrome, this check will not be satisfied and we will return -1 in that case.
    If the first and last characters are equal, then increment first index and decrement last index until first index is less than string_length/2.
  Complexity: O(n) since check for palindrome is only done once. 

*/

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

bool isPalin(string str){
    int begin = -1; 
    int end = str.size();
    while(++begin < --end){
        if(str[begin] != str[end])
            return false;
    }
    return true;
}

int palinIdx(string str){
    for(int i=0; i < str.size()/2; ++i){
        if(str[i] != str[str.size() - 1 -i]){
            if(isPalin(str.substr(0, i) + str.substr(i+1, str.size()-1))){
                return i;
            }else{
                return str.size()-1 -i;
            }
        }
            
    }
    return -1;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */  
    int n;
    cin >> n;
    while(n--){
        string str;
        cin >> str;
        cout << palinIdx(str) << endl;
    }
    return 0;
}

