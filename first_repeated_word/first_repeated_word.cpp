#include <iostream>
#include <unordered_set>
#include <string>

/* This program prints the first repeated word in a sentence. 
   The delimiters being tab, space, new line, semi colon, colon, comma, full-stop and hyphen 
*/
int main(){
  std::string str = "I have:::.-	had a long long day";

  std::unordered_set<std::string> mSet;
  
  size_t newpos ;
  size_t pos = 0;
  bool success = false;

  while(pos != std::string::npos){
    newpos = str.find_first_of(" \t\n:-.,;", pos);
    if(pos != newpos){
      std::string temp = str.substr(pos, newpos-pos);
      std::cout << temp << std::endl;
      if(mSet.find(temp) == mSet.end()){
        mSet.insert(temp);
      }else{
        success = true;
        std::cout << temp << std::endl;
        break;
      }
    }
    pos = newpos+1;
  }

  if(! success){
    std::cout << "" << std::endl;
  }
}
