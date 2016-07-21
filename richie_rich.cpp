/*
  @author: Narasimha Murthy
  Problem Link: https://www.hackerrank.com/challenges/richie-rich

  Algorithm: 
    First find the possible palindrome by using k changes. Then try to make it the largest by replacing lesser numbers with 9.
*/

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

string largestPalinNum(string str, int k){
    string orig(str);
    int begin = -1;
    int end = str.size();
    while(++begin <= --end){
        if(str[begin] != str[end]){
            if(k-- != 0){
                if(str[begin] >= str[end]){
                    str[end] = str[begin];
                }else{
                    str[begin] = str[end];
                }
                
            }else{
                return "-1";
            }
        }
    }
    if(k > 0){
        int begin = -1;
        int end = str.size();
        while(++begin <= --end ){
            if(begin == end ){
                if(str[begin] != '9' && k >= 1){
                    str[begin] = '9';
                    --k;
                }
                break;
            }
            
            if(begin < end && str[begin] != '9'){
                if((str[begin] != orig[begin] || str[end] != orig[end]) && k >= 1){
                    
                        str[end] = '9';
                        str[begin] = '9';
                        --k;
                  
                }else if(str[begin] == orig[begin] && str[end] == orig[end] && k >= 2){
                        str[end] = '9';
                        str[begin] = '9';
                        --k; --k;
                }
            }
        }
    }
    return str;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int n,k;
    cin >> n;
    cin >> k;
    string num;
    cin >> num;
    cout << largestPalinNum(num, k) << endl;
    return 0;
}
