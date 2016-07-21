/*
  @author: Narasimha Murthy

  Algorithm:
    This is a basic sliding window algorithm. Keep a window which contains at most 2 distinct characters, which can be determined using a hash map
*/

#include <iostream>
#include <unordered_map>

std::string longestSub(std::string str){
  std::unordered_map<char, int> map;
  int begin = 0;
  int end = 0;

  while(map.size() < 2){
    if(map.count(str[end]) > 0){
      ++map[str[end]];
    }else{
      map[str[end]] = 1;
    }
    ++end;
  }

  int max_begin = begin;
  int max_end = end;
  int max_len = end - begin + 1;
  for(int i=end; i < str.size(); ++i){
    if(map.count(str[i]) > 0){
      ++map[str[i]];
    }else{
      map[str[i]] = 1;
      while(map.size() > 2){
        --map[str[begin]];
        if(map[str[begin]] == 0){
          map.erase(str[begin]);
        }
        ++begin;
      }
    }
    if(i - begin + 1 > max_len){
      max_len = i - begin + 1;
      max_begin = begin;
      max_end = i;
    }
  }

  return str.substr(max_begin, max_len);
}

int main(){

  std::string word("abababababacaaaaabbbbb");
  std::cout << "String is " << word << std::endl;
//  std::vector<std::string> vec;
//  vec = longest_sub(word);
  std::cout << "Longest substring is " << longestSub(word) << std::endl;
//  printVector(vec);
}


