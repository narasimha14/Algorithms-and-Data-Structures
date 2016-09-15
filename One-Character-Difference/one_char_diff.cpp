#include <iostream>
#include <unordered_set>
#include <vector>
#include <string>
using std::string;
using std::unordered_set;

/*
  This is a program to find if there is any string that differs from the given string by just one character.
*/

int main(){
  std::vector<string> vec {"banas", "bana", "apple", "orange"};
  string pat("banana");
//  string alph2("1234567890abcdefghijklmnopqrstuvwxyz ");
  string alph;
  for(int i=0; i < 256; ++i){
    alph += i;
  }
  //Extra check by deleting one character and checking
  alph += " "; 
  string tmp;
  unordered_set<string> s;
  for(int i=0; i <vec.size(); ++i){
    s.insert(vec[i]);
  } 
  unordered_set<string>::const_iterator p = s.begin();
  while(p != s.end()){
    std::cout << *p << std::endl;
    ++p;
  }

  bool found = false;
  for(int i=0; i < pat.size(); ++i){
    for(int j=0; j < alph.size(); ++j ){
      tmp = pat;
      if( j == alph.size() - 1){
        tmp.erase(i,1);
      }else{
        tmp.replace(i, 1,1, alph[j]);
      }
      
      if(s.find(tmp) != s.end() ){
        std::cout << tmp << " differs from " << pat << " by one character "<< std::endl;
        found = true;
        break;
      }
    }
    if(found) break;
  }
  if(! found){
    std::cout << "No match" << std::endl;
  }
}
