/**
  Following is an extract of the question from the Baidu Coding Test:
  Implement a Calendar class which supports two operations:

  Schedule events
  Find time windows which are overbooked and find the associated conflicted events.
  Instructions

  Please implement Schedule and FindConflictedTimeWindows. 
  The return value of FindConflictedTimeWindows should be a list of ConflictedTimeWindow objects ordered by their start_time from earliest to latest.
  Please be aware that each ConflictedTimeWindow should contain ALL the conflicted events within the associated time period.

  For example,

  Calendar calendar = Calendar()
  calendar.Schedule(new Event(4, "2014-01-02 10:00", "2014-01-02 11:00"))
  calendar.Schedule(new Event(5, "2014-01-02 09:30", "2014-01-02 11:30"))
  calendar.Schedule(new Event(6, "2014-01-02 08:30", "2014-01-02 12:30"))

  calendar.FindConflictedTimeWindows()
  should return something like the following
  [ConflictedTimeWindow("2014-01-02 09:30", "2014-01-02 10:00", { 5, 6 }),
   ConflictedTimeWindow("2014-01-02 10:00", "2014-01-02 11:00", { 4, 5, 6 }),
   ConflictedTimeWindow("2014-01-02 11:00", "2014-01-02 11:30", { 5, 6 }]


  Algorithm:
    Basically, the idea is to sort all the times and do a sweep-line across them and look for interesting times
**/

#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

class ConflictedTimeWindow {
 public:
  ConflictedTimeWindow(const string& start_date, const string& end_date, const set<int>& conflicted_event_ids) : start_date_(start_date), end_date_(end_date), conflicted_event_ids_(conflicted_event_ids) {}

  string start_date() { return start_date_; }
  string end_date() { return end_date_; }
  set<int> conflicted_event_ids() { return conflicted_event_ids_; }

 private:
  string start_date_;
  string end_date_;
  set<int> conflicted_event_ids_;
};

/* This utility converts date and time format yyyy-mm-dd hh:mm to epoch seconds*/
time_t convertDateToSeconds(std::string time){
  std::string::size_type sz;
  int year = std::stoi(time, &sz);
  time = time.substr(sz+1, time.size());
  int month = std::stoi(time, &sz);

  time = time.substr(sz+1, time.size());
  int date = std::stoi(time, &sz);
  time = time.substr(sz+1, time.size());
  int hour = std::stoi(time, &sz);
  time = time.substr(sz+1, time.size());
  int min = std::stoi(time, &sz);

  struct tm tmpTime = {.tm_mday=date, .tm_year=(year - 1900), .tm_mon = month-1, .tm_min = min, .tm_hour = hour};
  time_t tmp = mktime(&tmpTime);
  return tmp;
}

/* This utility converts epoch seconds to date and time format yyyy-mm-dd hh:mm*/
std::string convertSecondsToDate(time_t time){
  struct tm* tmpTime = localtime(&time);
  std::string out("");
  out += std::to_string(tmpTime->tm_year+1900);
  out += "-";
  if(tmpTime->tm_mon+1 < 10)
    out += "0";
  out += std::to_string(tmpTime->tm_mon+1);
  out += "-";
  if(tmpTime->tm_mday < 10)
    out += "0";
  out += std::to_string(tmpTime->tm_mday);
  out += " ";
  if(tmpTime->tm_hour < 10)
    out += "0";
  out += std::to_string(tmpTime->tm_hour);
  out += ":";
  if(tmpTime->tm_min < 10)
    out += "0";
  out += std::to_string(tmpTime->tm_min);
  return out;
}


class Event {
 public:
  Event(const int id, const string& start_date, const string& end_date) : id_(id), start_date_(start_date), end_date_(end_date) {}

  int id() { return id_; };
  string start_date() { return start_date_; }
  string end_date() { return end_date_; }

 private:
  int id_;
  string start_date_;
  string end_date_;
};

void printVec(std::vector< std::pair< std::pair<time_t, int> ,bool > > vec){
  for(int i=0; i < vec.size(); ++i){
    std::cout << vec[i].first.first << " " << vec[i].first.second << " " << ( vec[i].second == false) << std::endl;
  }
}

class Calendar {
 public:
  // Should allow multiple events to be scheduled over the same time window.
  void Schedule(Event* event) {
    // IMPLEMENT ME
    // Convert date to epoch seconds and save it with the event id and a marker to know if it is a start date or end date
    times.push_back( std::make_pair( std::make_pair( convertDateToSeconds( event->start_date() ), event->id() ), true) ) ;    
    times.push_back( std::make_pair( std::make_pair( convertDateToSeconds( event->end_date() ), event->id() ), false) ) ;    
  }

  vector<ConflictedTimeWindow> FindConflictedTimeWindows() {
    // IMPLEMENT ME
    // Sort the start and end times as if they were the same
    std::sort(times.begin(), times.end()); 
    vector<ConflictedTimeWindow> output;
    // Keep track of ongoign events
    std::set<int> ongoing;
    ongoing.insert(times[0].first.second);

    long starttime;
    for(int i=1; i < times.size(); ++i){
      // If start time, add this to the ongoing events' list and add the ongoing events to this event's conflicted list and update the starttime for the next conflict
      if( times[i].second == true){
        ongoing.insert(times[i].first.second);
        starttime = times[i].first.first;
        if( ongoing.size() > 1 ){
          output.push_back( ConflictedTimeWindow(convertSecondsToDate( starttime) , convertSecondsToDate( times[i+1].first.first), ongoing));
          starttime = times[i+1].first.first;
        }
      }else{
      // If end time, then add this conflict if not already added and update the start time and remove this from the ongoing event list
        if(ongoing.size() > 1 && starttime != times[i].first.first){
          output.push_back( ConflictedTimeWindow(convertSecondsToDate( starttime) , convertSecondsToDate( times[i].first.first), ongoing));
          starttime = times[i].first.first;
        }
        ongoing.erase(times[i].first.second);
      } 
    }
    return output;
  }

  private:
    // parameters: start/end date in epoch seconds, event id, marker to know if start_date/end date
    std::vector<std::pair< std::pair<time_t, int> , bool> > times;
};

// Helper Function for logging
string ToString(const set<int>& input) {
  ostringstream sstream;
  sstream << "[";
  bool has_data = false;
  for (set<int>::iterator it = input.begin(); it != input.end(); ++it) {
    has_data = true;
    sstream << *it;
    sstream << ", ";
  }
  string output = sstream.str();
  if (has_data) {
    output = output.substr(0, output.length() - 2);
  }
  return output + "]";
}

#ifndef __main__
#define __main__

int main(int argc, char* argv[]) {
  Calendar calendar;
  calendar.Schedule(new Event(1, "2014-01-01 10:00", "2014-01-01 11:00"));
  calendar.Schedule(new Event(2, "2014-01-01 11:00", "2014-01-01 12:00"));
  calendar.Schedule(new Event(3, "2014-01-01 12:00", "2014-01-01 13:00"));

  calendar.Schedule(new Event(4, "2014-01-02 10:00", "2014-01-02 11:00"));
  calendar.Schedule(new Event(5, "2014-01-02 09:30", "2014-01-02 11:30"));
  calendar.Schedule(new Event(6, "2014-01-02 08:30", "2014-01-02 12:30"));

  calendar.Schedule(new Event(7, "2014-01-03 10:00", "2014-01-03 11:00"));
  calendar.Schedule(new Event(8, "2014-01-03 09:30", "2014-01-03 10:30"));
  calendar.Schedule(new Event(9, "2014-01-03 09:45", "2014-01-03 10:45"));
  vector<ConflictedTimeWindow> conflicted_time_windows = calendar.FindConflictedTimeWindows();
  for (size_t i = 0; i < conflicted_time_windows.size(); ++i) {
    cout << conflicted_time_windows[i].start_date() << "-" << conflicted_time_windows[i].end_date() << ToString(conflicted_time_windows[i].conflicted_event_ids()) << endl;
  }
  // should print something like the following
  // 2014-01-02 09:30-2014-01-02 10:00[5, 6]
  // 2014-01-02 10:00-2014-01-02 11:00[4, 5, 6]
  // 2014-01-02 11:00-2014-01-02 11:30[5, 6]
  // 2014-01-03 09:45-2014-01-03 10:00[8, 9]
  // 2014-01-03 10:00-2014-01-03 10:30[7, 8, 9]
  // 2014-01-03 10:30-2014-01-03 10:45[7, 9]
}

#endif
