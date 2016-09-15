/*
  @author: Narasimha Murthy
  Problem Link: https://www.hackerrank.com/challenges/sherlock-and-valid-string/

  Algorithm:
    Get character count of all characters in the string.
    If occurrence of all characters are same in the string then output "YES"
    If just one character has a different count then "YES"
    If it fails the above two, then "NO"
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
    string s;
    cin >> s;
    
    vector<int> vec(26,0);
    for(int i=0; i < s.size();++i){
        ++vec[s[i] - 'a'];
    }
    sort(vec.begin(), vec.end());
    int begin = 0;
    while(vec[begin] == 0 && begin < vec.size()){
        ++begin;
    }
    
    bool valid = false;
    //If same occurrence of all characters then "YES"
    if(vec[begin] == vec[vec.size()-1]){
        valid = true;
    }
    // If just one char has a different count than others then "YES" or else "NO"
    else{
        unordered_map<int, int> charCount;
        while(begin < vec.size()){
            ++charCount[vec[begin++]];
        }
        if(charCount.size() == 1)
            valid = true;
        else if(charCount.size() == 2){
            unordered_map<int, int>::const_iterator itr = charCount.begin();
            while(itr != charCount.end()){
                if(itr->second == 1){
                    valid = true;
                }
                ++itr;
            }
        }
    }
    if(valid)
        cout << "YES";
    else
        cout << "NO";
    return 0;
}

