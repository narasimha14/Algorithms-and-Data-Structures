/*
  @author: Narasimha Murthy
  Algorithm:
    This algorithm works on the fact that if you XOR an element with itself, it will equal 0.
*/

class Solution {
  public:
    int missingNumber(vector<int>& nums) {
      int sum = 0;
      for(int i=1; i < nums.size()+1; ++i){
        sum ^= i;
      }
      for(int i=0; i < nums.size();++i){
        sum ^= nums[i];
      }
      return sum;
    }
};
