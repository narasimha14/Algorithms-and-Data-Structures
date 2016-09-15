/*
  @author: Narasimha Murthy
  Problem Link: https://www.hackerrank.com/challenges/string-similarity

  Algorithm:
    A modified version of the algorithm for finding the partial match table in KMP string matching algorithm.
*/

#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <cstdlib>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

long long int stringSimilarity(char pat[]) {
    int len = strlen(pat);
    std::vector<int> table(len);
    int i=1, j =0;
  int k;
  while( i < len && pat[i] == pat[j]){
    ++i;
    ++j;
  }
  table[1] = j;

  int a = 1;
  for(k=2, --j; k < len ; ++k, --j){
    if(j < 0 || k + table[k-a] >= i){
      if(j<0){
        j = 0;
        i = k;
      }
      while( i < len && j < len && pat[i] == pat[j]){
        ++i;
        ++j;
      }
      table[k] = j;
      a = k;
    }else{
      table[k] = table[k-a];
    }
  }
    long long sum = len;
    for(int i=0; i < table.size(); ++i){
        sum += table[i];
    }
   return sum;
}
int main() {
    int t, i;
    scanf("%d",&t);
    char a[100001];
    for (i=0;i<t;i++) {
        scanf("%s",a);
        long long int res=stringSimilarity(a);
        printf("%lld\n",res);  
    }
    
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */    
    return 0;
}

