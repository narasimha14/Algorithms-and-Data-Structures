#include <iostream>
#include <vector>

/*
  This is an efficient solution to the leet code question : https://leetcode.com/problems/sort-colors/
  Runs in O(n) time in a single sweep
*/

void swap(int& a, int& b){
  int tmp = a;
  a = b;
  b = tmp;
}

void printVec(std::vector<int> vec){
  for(int i=0; i < vec.size(); ++i){
    std::cout << vec[i] << " " ;
  }
  std::cout << "" << std::endl;
}

void sortColor(std::vector<int>& vec){
  int red = 0;
  int blue = vec.size() - 1;
  int i =0;
  while(i <= blue){
    if(vec[i] == 0){
      swap(vec[i], vec[red]);
      ++red;
      ++i;
    }else if(vec[i] == 2){
      swap(vec[i], vec[blue]);
      --blue;
    }else{
      ++i;
    }
  }
}

int main(){
  std::vector<int> vec{1,2,0,1,1,1,2,2,0,0,0,1,2};
  sortColor(vec); 
  printVec(vec);
}
