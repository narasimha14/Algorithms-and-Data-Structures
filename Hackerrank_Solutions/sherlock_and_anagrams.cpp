/*
  @author: Narasimha Murthy
  Problem Link: https://www.hackerrank.com/challenges/sherlock-and-anagrams 

  Algorithm: 
    For each char in the string, find the subtrings of all lengths starting with that char and sort it.
    If a substring occurs n times then, there are sigma(n-1) pairs. So we add this value i.e. n(n-1)/2 to our answer. 
  
  Complexity : O(n^2) since we dynamically build the substrings 
*/

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
using namespace std;


// Algorithm: For each char in the string, find the subtrings of all lengths starting with that char and sort it.
// If a substring occurs n times then, there are sigma(n-1) pairs. So we add this value i.e. n(n-1)/2 to our answer. 
// Complexity : O(n^2) since we dynamically build the substrings 
int numberOfPairs(string str){
    unordered_map<string, int> mMap;
    for(int i=0; i < str.size();++i){
        for(int j=1; j +i -1 < str.size();++j){
            string s = str.substr(i,j);
            
            sort(s.begin(), s.end());
          
            ++mMap[s];
        }
    }
    unordered_map<string, int>::const_iterator itr = mMap.begin();
    int sum =0;
    while(itr != mMap.end()){
        sum += (itr->second)*(itr->second -1)/2;
        ++itr;
    }
    return sum;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int n;
    cin >> n;
    while(n--){
        string str;
        cin >> str;
        cout << numberOfPairs(str) << endl;
    }
    return 0;
}
