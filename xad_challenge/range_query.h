#include "usertype.h"
#include "compare.h"
#include <algorithm>
#include <ctime>
/*
  @author: Narasimha Murthy
  This file contains the query algorithm
  Algorithm: It sorts the input data and does a binary search on the sorted data to find the index of the left and right element.
  Once we know the indices, the difference between them gives the number of elements in that range
  Complexity Analysis (n -> total number of objects):
    Space Complexity: O(n)
    Time Complexity:
      To build the sorted input: O( nlogn )
      Query: O(logn)
*/

/*
  An enumerator to define the operations that can be performed on the data-set
*/

enum{
  GREATER, 
  LESSER,
  EQUAL
};

/*
  This is a template class that takes in the input and does the query operations to get the number of object in a given range
  @tparam T : May contain int, float, string or any User-defined Data Type
*/

template<typename T>
class RangeQuery{
  public:
    /* Default Constructor */
    RangeQuery():vec(){ }

    /* Contructor that takes a vector of input objects and sorts it. Sorting is necessary to binary search. 
       If this constructor is used, no need to call the build method */
    RangeQuery(std::vector<T> input) : vec(input){
      clock_t begin, end;
      begin = std::clock();

      std::sort(vec.begin(), vec.end(), compare<T>());

      end = std::clock();
      std::cout << "Initializing and building the data set of size " << vec.size() << " took " << end - begin << " microSeconds" << std::endl;
    }

    /* Used along with the default constructor to build the sorted input data from a vector of data */
    void build(std::vector<T> input){
      clock_t begin, end;
      begin = std::clock();

      vec = input;
      std::sort(vec.begin(), vec.end(), compare<T>());

      end = std::clock();
      std::cout << "Building the data set of size " << vec.size() << " took " << end - begin << " microSeconds" << std::endl;
    }

    /* This is a method to get the number of objects that lies in the given range i.e. (left, right)
       @param left : The value of the left object in the range interval
       @param right : The value of the right object in the range interval
       @return The number of objects that are greater than left and lesser than right, not including left and right
    */
    int getRange(const T left, const T right){
      return query<T>( left, right);
    }

    /* This is a method to get the number of objects that are greater, lesser or equal to the given value
       @param val : The value of the object
       @param op : The operation indicating greater, lesser or equal
       @return The number of objects that are greater or lesser than or equal to the given value
    */
    int getVal(const T val, int op){
      return queryOp<T>(val, op);
    }

    /*
      This is a method to clear the data set
    */
    void clear(){
      vec.clear();
    }

  private:
    /*
      A method to query the number of objects in the given range when the object type is user-defined
      @tparam U: User-defined type, int, float or string
    */
    template<class U>
    int query( const U left, const U right){
      clock_t begin, end;
      begin = std::clock();

      // Gets the number of objects greater than left
      int greater_l = vec.end() - std::upper_bound(vec.begin(), vec.end(), left, compare<U>());
      // Gets the number of objects greater than right
      int greater_r = vec.end() - std::lower_bound(vec.begin(), vec.end(), right, compare<U>());

      end = std::clock();
      std::cout << "Querying the data set took " << end - begin << " microSeconds" << std::endl;

      // Returns the intersection of the two
      return greater_l < greater_r ? 0 : (greater_l - greater_r);
    }
   
    /*
      This is a method to query the number of objects that are greater/lesser than or equal to a value
      @param op : Determines whether to perform greater than or lesser than or equal to operation
    */
    template<class U>
    int queryOp( const U val, const int op){
      clock_t begin, end;
      begin = std::clock();

      int out = 0;
      if(op == GREATER){  
        out = vec.end() - std::upper_bound(vec.begin(), vec.end(), val, compare<U>());
      }else if(op == LESSER){
        out = std::lower_bound(vec.begin(), vec.end(), val, compare<U>()) - vec.begin();
      }else if(op == EQUAL){
        out = std::upper_bound(vec.begin(), vec.end(), val, compare<U>()) - std::lower_bound(vec.begin(), vec.end(), val, compare<U>());
      }

      end = std::clock();
      std::cout << "Querying the data set took " << end - begin << " microSeconds" << std::endl;

      return out;
    }

    /* The input objects in sorted order */
    std::vector<T> vec;
};

