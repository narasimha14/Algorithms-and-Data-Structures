#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

/*
  This is an iterative version of merge sort that makes use of queues
*/

void printVec(std::vector<int> vec){
  std::vector<int>::const_iterator p = vec.begin();
  while(p != vec.end()){
    std::cout << *p++ << " ";
  }
  std::cout << "" << std::endl;
}
std::vector<int> merge( std::vector<int> a, std::vector<int> b){
  std::vector<int> c(a.size() + b.size());
  int index = a.size() + b.size() - 1;
  int i = a.size() - 1;
  int j = b.size() - 1;
  while( i >= 0 && j >= 0){
    if( a[i] > b[j]){
      c[index--] = a[i--];
    }else{
      c[index--] = b[j--];
    }
  }
  while( i >= 0 ){
    c[index--] = a[i--];
  }
  while( j >= 0){
    c[index--] = b[j--];
  }
  return c;
}


int main(){
  std::vector<int> a {5,1,9,4,3,10};
  std::queue<std::vector<int> > q;
  std::vector<int>::const_iterator p = a.begin();

  while(p != a.end()){
    std::vector<int> tmp;
    tmp.clear();
    tmp.push_back(*p++);
    q.push(tmp);
  }

  while( q.size() > 1 ){
    std::vector<int> tmp1;
    tmp1.clear();
    tmp1 = q.front();
    q.pop();
    q.push( merge(tmp1, q.front()));
    q.pop();
  }
  printVec(q.front());
  q.pop();
}
