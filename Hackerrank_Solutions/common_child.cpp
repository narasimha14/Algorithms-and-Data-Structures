/*
  @author: Narasimha Murthy
  Problem Link: https://www.hackerrank.com/challenges/common-child/

  Algorithm:
    This is just a Dynamic Programming solution for finding the lowest common substring (LCS).
*/

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int lcs(string s, string t, vector< vector<int> > vec){
    if(vec[s.size()][t.size()] != -1){
        return vec[s.size()][t.size()];
    }
    if(s.size() == 0 || t.size() == 0){
        return 0;
    }
    if(s[0] == t[0] ){
        vec[s.size()][t.size()] = 1 + lcs(s.substr(0, s.size()-1), t.substr(0, t.size()-1), vec);
    }else{
        vec[s.size()][t.size()] = max(lcs(s, t.substr(0, t.size()-1), vec), lcs(s.substr(0, s.size()-1), t, vec));
    }
    
    return vec[s.size()][t.size()];
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */  
    string s,t;
    cin >> s;
    cin >> t;
    vector<int> vec(t.size()+1,0);
    vector<vector<int> > vec2(s.size()+1, vec);
    for(int i=0; i <= s.size(); ++i){
        for(int j=0; j <= t.size();++j){
            if(i==0 || j ==0){
                vec2[i][j] = 0;
            }else if(s[i-1] == t[j-1]){
                vec2[i][j] = vec2[i-1][j-1] + 1;
            }else{
                vec2[i][j] = max(vec2[i][j-1], vec2[i-1][j]);
            }
            
        }
    }
    //cout << maxLen << endl;
    cout << lcs(s,t, vec2) << endl;
    return 0;
}

