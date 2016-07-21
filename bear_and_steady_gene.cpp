/*
  @author: Narasimha Murthy
  Problem Link: https://www.hackerrank.com/challenges/bear-and-steady-gene

  Algorithm:
    Get a count of all the characters.
    If the count of either of A, G, C or T is not equal to string length/4, then starting from the beginning keep removing characters until they are equal.
    If on removing, the count of either characters goes below length/4 then add characters from the beginning.
*/

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
using namespace std;

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    unordered_map<char, int> mMap;
    int len;
    cin >> len;
    string str;
    cin >> str;
    
    //Get a count of all chars in the string
    for(int i=0; i < str.size(); ++i){
        ++mMap[str[i]];
    }
    int minLength = 0;
    if( mMap['A'] != len/4 || mMap['C'] != len/4 || mMap['G'] != len/4 || mMap['T'] != len/4){
        minLength = len;
        for(int right=0, left =0; right < len; ++right){
            --mMap[str[right]];
            while(mMap['A'] <= len/4 && mMap['C'] <= len/4 && mMap['G'] <= len/4 && mMap['T'] <= len/4 && left <= right){
                minLength = min(minLength, right - left + 1);
                ++mMap[str[left++]];
            }
        }
        
    }
    cout << minLength << endl;
    
    return 0;
}

