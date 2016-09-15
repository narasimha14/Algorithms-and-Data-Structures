/*
  @author: Narasimha Murthy
  Problem Link: https://www.hackerrank.com/challenges/morgan-and-a-string

  Algorithm:
    Traverse both the string one character at a time starting from the beginning.
    Append to output string whichever is greater among the two.
    If they both are equal, then we compare both strings until we find a lexigographically lesser one 
    and append to the output all the characters of this string starting from the index where both the strings were equal
  Complexity: Linear
*/

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

string minimalString(string s, string t){
    int idx1 = 0;
    int idx2 = 0;
    string out;
    while(idx1 < s.size() && idx2 < t.size()){
        if(s[idx1] < t[idx2])
            out += s[idx1++];
        else if(s[idx1] > t[idx2])
            out += t[idx2++];
        else{
            int x = idx1;
            int y = idx2;
            while(x < s.size() && y < t.size()){
                if(s[x] != t[y]){
                    break;
                }else if(s[x] > s[idx1]){
                    out += s.substr(idx1, x-idx1);
                    out += t.substr(idx2, y-idx2);
                    idx1 = x;
                    idx2 = y;
                }
                ++x;
                ++y;
            }
            
             if(x == s.size()) {
                out += t[idx2++];
             }else if (y == t.size()) {
                out += s[idx1++];
             }else {
               if(s[x] < t[y]) {
                   out += s[idx1++];
                }else{
                   out += t[idx2++];    
                }
             }
        }
    }
    if(idx1 == s.size()){
        while(idx2 < t.size()){
            out += t[idx2++];
        }
    }else{
        while(idx1 < s.size()){
            out += s[idx1++];
        }
    }
    return out;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */  
    int n;
    cin >> n;
    while(n--){
        string str1, str2;
        cin >> str1;
        cin >> str2;
        cout << minimalString(str1, str2) << endl;
    }
    return 0;
}
