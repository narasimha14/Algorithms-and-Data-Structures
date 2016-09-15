This is a DP problem that asks us to find the number of ways to get to a score in an American Football game with the below rules:

6 points for the touchdown
1 point for the extra point (kicked)
2 points for a safety or a conversion (extra try after a touchdown)
3 points for a field goal

DP recurrence relation can be formulated as below:

  count(score, td) -> number of ways to reach to "score", 
  td => true indicates that touchdown is scored currently, false indicates no touchdown
 
                     |  1                                                                       if score is 0

                     |  0                                                                       if score < 0

  count(score, td) = |  count(score-1, false) + count(score-2, false) + count(score, false)     if td is true

                     |  count(score-6, true) + count(score-3, false)                            otherwise

  count(score, 0)  will be our required solution
  Time Complexity : (-)(score) (theta of score)

This formula can be simplified to just count(score) = count(score-6) + count(score -7) + count(score-8) + count(score-3)
But the author feels the previous formulation is more understandable.

