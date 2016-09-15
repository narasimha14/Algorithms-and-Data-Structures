#include <iostream>
#include <unordered_map>
using namespace std;

/*
   This is a solution to the LeetCode Challenge https://leetcode.com/problems/minimum-window-substring/
   @author: Narasimha Murthy
   The basic idea is to first find a window between "begin" and "end" that contains all the required chars.
   Then starting from "end", keep adding the chars to the window. Once you encounter a char that is same as char at "begin",
   keep deleting chars from the "begin" of the window you reach a char which is in 't' and whose count is same as it's count in 't'.
   Update the minimum window length accordingly
*/

void printMap(unordered_map<char,int> map){
  unordered_map<char, int>::const_iterator itr = map.begin();
  while(itr != map.end()){
    cout << itr->first << ", " << itr->second << endl;
    ++itr;
  }
}

string minWindow(string s, string t){
  unordered_map<char, int> tMap, dup, windowMap;
  for(int i=0; i < t.size(); ++i){
    if(tMap.count(t[i]) == 0){
      //Add the new element to the map
      tMap[t[i]] = 1;
    }else{
      ++tMap[t[i]];
    }
  }

  dup = tMap;

  //Find the starting point of the first window
  int begin = 0, end = 0;
  while(end < s.size() && (tMap.count(s[end]) == 0) ){
    ++end;
  }

  //Starting with the starting point, find a window
  begin = end;
  
  while(dup.size() > 0 && end < s.size()){
    if(dup.count(s[end]) > 0){
      --dup[s[end]];
      if(dup[s[end]] == 0){
        dup.erase(s[end]);
      }
    }
      if(windowMap.count(s[end]) == 0 ){
        windowMap[s[end]] = 1;
      }else{
        ++windowMap[s[end]];
      }
      if(dup.size() != 0)
        ++end;
  }
    
  if(dup.size() != 0){
    return "";
  }
  
  //Remove unwanted repeated chars from the window
  while(begin < end){
    if(tMap[s[begin]] < windowMap[s[begin]]){
      --windowMap[s[begin++]];
    }else{
      break;
    }
  }

  //Find the minimum window. Scan through each char from "end" inserting into windowMap until you reach the char equal to "begin" char.
  //Start removing chars from begin until you reach a char whose count is same as tMap. Update the min len 
  int min_begin = begin;
  int min_end = end; 
  int min_len = end - begin + 1;
  while(++end < s.size()){
        ++windowMap[s[end]];
      if(s[end] == s[begin]){
        while(tMap[s[begin]] < windowMap[s[begin]]){
              --windowMap[s[begin++]];
        }
      }
      if(end - begin + 1 < min_len){
        min_len = end - begin + 1;
        min_begin = begin;
        min_end = end;
      }
  }
  return s.substr(min_begin, min_len);
}

int main(){
  std::cout <<  minWindow("adobecodebanc", "abc") << std::endl;
}
