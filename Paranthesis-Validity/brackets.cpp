#include <iostream>
#include <stack>
#include <string>

/*
  This is a program to find the validity of a sentence with paranthesis
*/

int main(){
  std::string in = "{{[]()}}";
  std::stack<char> expected;
  bool isValid = true;
  for(int i=0; i < in.size(); ++i){
    if(in[i] == '{' || in[i] == '(' || in[i] == '['){
      if(in[i] == '{'){
        expected.push('}');
      }
      else if(in[i] == '('){
        expected.push(')');
      }
      else if(in[i] == '['){
        expected.push(']');
      }
    }else{
      if(expected.empty()){
        isValid = false;
        break;
      } 
      if(expected.top() == in[i]){
        expected.pop();
        isValid = true;
      }
    }
  }
  if(!expected.empty() || ! isValid){
    std::cout << "NO" << std::endl;
  }else{
    std::cout << "YES" << std::endl;
  }
}
