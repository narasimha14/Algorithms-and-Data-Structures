#include <iostream>
#include <vector>

/*
  This program find the least number of bits to be flipped so that the number of 1s in the array is maximized
*/

int main(){
//  std::vector<int> vec{1,0,1,0,1,1,0,1};
//  std::vector<int> vec{1,1,1,0,1,1,1};
//  std::vector<int> vec{0,0,0,0,0,0,0,0};
  std::vector<int> vec{1,0,0,1,0,0,1,0};
  
  //Kadane's Algorithm : Convert all 0s to -1 and find the indices of the minimum sub array and flip the bits within the indices
  int count = 0;
  if (vec.size() == 0) count = 0;
  else{
  int min_ending_here = vec[0];
  int min_so_far = vec[0];
  int start_index = 0;
  int min_start_index = 0;
  int end_index = -1;
  int tmpVec = 1;
  count = vec[0];
  for(int i = 1; i < vec.size(); ++i){
    if(vec[i] == 0){
      tmpVec = -1;
    }
    else{
      tmpVec = 1;
      ++count;
    }
    if(tmpVec < min_ending_here + tmpVec){
      min_ending_here = tmpVec;
      start_index = i;
    }else{
      min_ending_here += tmpVec;
    }

    if(min_ending_here <= min_so_far){
      min_so_far = min_ending_here;
      min_start_index = start_index;
      end_index = i;
    }
  }
  if( count != vec.size())
    for(int i = min_start_index; i <= end_index; ++i){
      if(vec[i] == 0){
        ++count;
      }else{
        --count;
      }
    }
  std::cout << min_start_index << "," << end_index << std::endl;
  }
  std::cout << count << std::endl;
}
