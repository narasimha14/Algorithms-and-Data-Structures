/*
  @author: Narasimha Murthy
  Algorithm:
    This is a straight forward sliding window using multi-set to store even the duplicate elements and get the maximum
*/

class Solution {
  public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
      multiset<int> mSet;
      vector<int> out;
      if(nums.size() == 0){
        return out;
      }
      for(int i=0; i <k; ++i){
        mSet.insert(-nums[i]);
      }
      out.push_back(-(*mSet.begin()));
      int begin = 0; 
      int end = k-1;
      for(int i = k; i < nums.size(); ++i){
        mSet.erase(mSet.find(-(nums[begin++])));
        mSet.insert(-nums[i]);
        out.push_back(-(*mSet.begin()));
      }
      return out;
    }

};
