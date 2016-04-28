Implement a Calendar class which supports two operations:

Schedule events
Find time windows which are overbooked and find the associated conflicted events.
Instructions

Please implement Schedule and FindConflictedTimeWindows. The return value of FindConflictedTimeWindows should be a list of ConflictedTimeWindow objects ordered by their start_time from earliest to latest. Please be aware that each ConflictedTimeWindow should contain ALL the conflicted events within the associated time period.

For example,

 Calendar calendar = Calendar()
 calendar.Schedule(new Event(4, "2014-01-02 10:00", "2014-01-02 11:00"))
 calendar.Schedule(new Event(5, "2014-01-02 09:30", "2014-01-02 11:30"))
 calendar.Schedule(new Event(6, "2014-01-02 08:30", "2014-01-02 12:30"))

 calendar.FindConflictedTimeWindows()
 // should return something like the following
 // [ConflictedTimeWindow("2014-01-02 09:30", "2014-01-02 10:00", { 5, 6 }),
 //  ConflictedTimeWindow("2014-01-02 10:00", "2014-01-02 11:00", { 4, 5, 6 }),
 //  ConflictedTimeWindow("2014-01-02 11:00", "2014-01-02 11:30", { 5, 6 }]
