#include <iostream>

/**
  @author: Narasimha Murthy
  count(score, td) -> number of ways to reach to "score", 
  td => true indicates that touchdown is scored currently, false indicates no touchdown
 
                     |  1									if score is 0
                     |  0									if score < 0
  count(score, td) = |  count(score-1, false) + count(score-2, false) + count(score, false)	if td is true
                     |  count(score-6, true) + count(score-3, false)				otherwise

  count(score, 0)  will be our required solution
  Time Complexity : (-)(score) (theta of score)

  This formula can be simplified to just count(score) = count(score-6) + count(score -7) + count(score-8) + count(score-3)
  But the author feels the previous formulation is more understandable.
**/



/* Recursion without Dynamic Programming */
int count(int score, bool td){
  if(score < 0){
    return 0;
  }
  if(score == 0){
    return 1;
  }

  if(td){
    return count(score-1, false) + count(score-2, false) + count(score, false);
  }

  return count(score-6, true) + count(score-3, false);
}


/* Recursive Dynamic Programming Solution */
int count_dp(int score, int td, int arr[][2]){
  if(score < 0){
    return 0;
  }
  if(score == 0){
    return 1;
  }
  if(arr[score][td] != -1){
    return arr[score][td];
  }

  if(td){
    return count_dp(score-1, 0, arr) + count_dp(score-2, 0, arr) + count_dp(score, 0, arr);
  }

  return count_dp(score-6, 1, arr) + count_dp(score-3, 0, arr);
}

/* Iterative Dynamic Programming Solution*/
int count_dp2(int score, bool td){
  
  int dp[score+1][2];

  // Initialize DP array
  for(int i=0; i <= score; ++i){
    if(i == 0){
      dp[i][0] = dp[i][1] = 1;
      continue;
    }
    dp[i][0] = -1;
    dp[i][1] = -1; 
  }

  for(int i =0; i <= score; ++i){
    for(int j=0; j < 2; ++j){
      if(dp[i][j] != -1){
        continue;
      }
      if(j == 0){
        dp[i][j] = ( i-6 >= 0 ? dp[i-6][1] : 0 ) + ( i-3 >= 0 ? dp[i-3][0] : 0);
//        std::cout << "dp[" << i <<"][" << j <<"] is " << dp[i][j] << std::endl;
      }else{
        dp[i][j] = ( i-1 >= 0 ? dp[i-1][0] : 0) + (i-2 >= 0 ? dp[i-2][0] : 0) + dp[i][0];
//        std::cout << "dp[" << i <<"][" << j <<"] is " << dp[i][j] << std::endl;
      }
    }
  }
  std::cout << dp[score][0] << std::endl;
  return dp[score][0];
}

int main(){
  int score = 30;
  std::cout << count(score, false) << std::endl;
  std::cout << count_dp2(score, false) << std::endl;

  // Initialize an array to store the previous sub-problem solutions
  int arr[score+1][2];
  for(int i =0; i <= score; ++i){
    if(i==0){
      arr[i][0]=arr[i][1] = 0;
    }else{
      arr[i][0] = arr[i][1] = -1;
    }
  }
  std::cout << count_dp(score, 0, arr) << std::endl;
}
