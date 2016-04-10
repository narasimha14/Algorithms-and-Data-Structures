#include <iostream>
#include <vector>

/* This is a solution to the hackerrank problem : https://www.hackerrank.com/challenges/candies 
   It does a two-time sweep, one in forward direction and the other in reverse direction and updates the candies according to the rules of the problem
*/

int main(){
  int n;
  std::cin >> n;
  std::vector<int> ratings;
  std::vector<int> candies;
    
  int input;
  for(int i = 0; i < n; ++i){
    std::cin >> input; 
    ratings.push_back(input);
  }
    
  candies.push_back(1);
  for(int i = 1; i < ratings.size(); ++i){
    if(ratings[i] > ratings[i-1]){
      candies.push_back(candies[i-1] + 1);
    }else{
        candies.push_back(1);
    }
  }
  

  int sum = candies[ratings.size()-1];
  for(int i= ratings.size()-2; i >= 0; --i){
    if(ratings[i] > ratings[i+1]){
      if(candies[i] <= candies[i+1]){
        candies[i] = candies[i+1]+1;
      }
    }
    sum += candies[i];
  }

  std::cout << sum << std::endl;

}
