#include <iostream>
#include <bitset>
#include <vector>
#include <cmath>
#include <iomanip>
#include <algorithm>

/*
  This is a short cut solution to the HackerRank problem on Uneaten Leaves. It creates a bit table for each entry of the number of caterpillars and then makes decision based on the same. Below is the problem description:

  K caterpillars are eating their way through N leaves, each caterpillar falls from leaf to leaf in a unique sequence, all caterpillars start at a twig at position 0 and falls onto the  leaves at position between 1 and N. 
  Each caterpillar j has as associated jump number Aj. A caterpillar with jump number j eats leaves at positions that are multiple of j. 
  It will proceed in the order j, 2j, 3j…. till it reaches the end of the leaves and it stops and build its cocoon.
  Given a set A of K elements K<-15, N<=10^9, we need to determine the number of uneaten leaves.

  Input:
  N= No of uneaten leaves.
  K= No. of caterpillars
  A = Array of integer jump numbers

  Output:
  The integer nu. Of uneaten leaves.

  Sample Input:
  10
  3
  2
  4
  5
  Output:
  4

  Explanation:
  [2, 4, 5] is a j member jump numbers, all leaves which are multiple of 2, 4, and 5 are eaten, leaves 1,3,7,9 are left, and thus the no. 4

*/


int getGcd(int a, int b){
  return b == 0 ? a : getGcd(b, a % b);
}

int getLcm(int a, int b){
  int temp = getGcd(a, b);
  return temp ? (a / temp * b) : 0;
}

int main(){
  std::vector<int> k{ 2, 4,5};
  double num = 10;
  std::vector<int> a;

  /* Not necessary and doesn't contribute to efficiency much, but optimized nonetheless */
  // Choose only those numbers that are not divisible by any other number in the 'k' vector
  std::sort(k.begin(), k.end());
  for(int i =0; i < k.size(); ++i){
    bool add = true;
    for(int j=0; j < a.size(); ++j){
      if( k[i] % a[j] == 0){
        add = false;
	break;
      }
    }
    if(add){
      a.push_back(k[i]);
      add = true;
    }
  }

  std::bitset<15> b;
  double total_count = 0;
  for(int i = 1; i < pow(2, a.size()); ++i){
    b.reset();

    //Convert to binary
    int count = 0;
    int n = i;
    do{
      b[count++] = n%2;
      n = n /2;
    }while(n > 1);

    b[count] = n;

    // Find the LCM and calculate the number of multiples
    int lcm = 1;
    for(int i = 0; i < a.size(); ++i){
      if( b[i] == 1){
        lcm = getLcm(lcm, a[i]);
      }
    }
    
    // If number of 1s in the bitset is even, subtract from the multiples, if odd add
    if( b.count() % 2 == 0){
      total_count -= std::floor( num/lcm ) ;
    }else{
      total_count += std::floor( num/lcm );
    }
  }

  double uneaten = num - total_count;

  std::cout << "Uneaten leaves are " << std::setprecision(9) << uneaten << std::endl;
  
} 
