/*
  @author: Narasimha Murthy
  Partial Match Table code copied from www.geeksforgeeks.org
  Algorithm:
    Concatenate the string with its reverse and compute the partial match for the concatenated string
    Remove from the reversed string the number of chars from left as calculated in the last entry of the partial match table and append to the string.
    This gives the shortest palindrome
*/

#include <iostream>
#include <string>
#include <vector>

// Method to reverse a string in-place
void reverse(std::string& str){
  int begin = -1;
  int end = str.size();

  while(++begin < --end){
    char tmp = str[begin];
    str[begin] = str[end];
    str[end] = tmp;
  }
}


// One of the steps of KMP Pattern Matching Algorithm to find the longest proper prefix which is also a suffix
void computePartialMatchTable(std::string& pat, std::vector<int>& table){
  int len=0;
  table[0] = 0;
  int i = 1;
  while(i < pat.size()){
    if(pat[i] == pat[len]){
      ++len;
      table[i] = len;
      ++i;
    }else{
      if(len == 0){
        table[i] = 0;
        ++i;
      }else{
        len = table[len-1];
      }
    }
  }
} 

std::string findShortestPalin(std::string str){

  std::string rev = str;
  reverse(rev);
  std::string concat = str + "#" + rev; // # is for separating reversed string from the original. Needed for test cases like str = "aaaaa"

  std::vector<int> table(concat.size());

  // Compute the partial match for the concatenated string and 
  // remove from the reversed string the number of chars from left as calculated in the last entry of the partial match table
  computePartialMatchTable(concat, table);

  return rev.substr(0, str.size() - table[concat.size()-1]) + str;

}

int main(){

  std::string str("abab");

  std::cout << "Shortest Palindrome is " << findShortestPalin(str) << std::endl;

}
