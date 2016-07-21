/*
  @author: Narasimha Murthy
  Algorithm:
    Traverse the array and negate the value of element at the index of the array element. If while traversing we reach a negative number, then this is the duplicate
*/

class Solution {
  public:
    int findDuplicate(vector<int>& nums) {
      for(int i=0; i < nums.size(); ++i){
        if(nums[abs(nums[i])] < 0){
          return abs(nums[i]);
        }else{
          nums[abs(nums[i])] = -nums[abs(nums[i])];
        }
      }
      return 0;
    }
};
