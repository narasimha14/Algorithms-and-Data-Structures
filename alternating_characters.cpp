/*
  @author: Narasimha Murthy
  Problem Link: https://www.hackerrank.com/challenges/alternating-characters
*/


#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int numDel(string str){
    if(str.size() <= 1)
        return 0;
    int count = 0;
    for(int i=0; i < str.size()-1; ++i){
        if(str[i] == str[i+1])
            ++count;
    }
    return count;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int n;
    cin >> n;
    while(n--){
        string str;
        cin >> str;
        cout << numDel(str) << endl;
    }
    return 0;
}

