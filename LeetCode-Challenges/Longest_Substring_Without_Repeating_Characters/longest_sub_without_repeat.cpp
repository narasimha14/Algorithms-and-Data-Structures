/*
  @author: Narasimha Murthy

  Algorithm:
    Uses a straight-forward hash map and a sliding window
*/

class Solution {
  public:
    int lengthOfLongestSubstring(string s) {
      if(s.size() == 0){
        return 0;
      }
      unordered_map<char, int> set;
      int max_len = 1;
      int cur_len = 1;
      set[s[0]] = 0;
      for(int i=1; i < s.size(); ++i){
        if(set.count(s[i]) == 0 || i-cur_len > set[s[i]]){
          ++cur_len;
        }else{
          if(cur_len > max_len){
            max_len = cur_len;
          }
          cur_len = i - set[s[i]];
        }
        set[s[i]] = i;
      }
      return cur_len > max_len ? cur_len : max_len;
    }

};
