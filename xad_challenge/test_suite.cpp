#include <iostream>
#include <vector>
#include "range_query.h"
#include <cassert>

/*
  @author: Narasimha Murthy
  This is an abstract base class for the test suite
  run(int size) is a purely virtual function that has to be defined by the derived classes
  The derived classes must be declared as friend classes since runQuery is declared private
*/
template <typename T>
class TestSuite{
  public:
    TestSuite():range(){}
    // Purely virtual method
    virtual int run(int size) = 0;
    // Derived classes
    friend class IntTestSuite;
    friend class FloatTestSuite;
    friend class StringTestSuite;
    friend class UserTypeTestSuite;
  private:
    // Method to build the data-set
    void build(std::vector<T> vec){
      range.build(vec);
    }

    // Method to run query to get number of values in a range
    bool runQuery( T left, T right, int expected){
      return (range.getRange(left, right) == expected);
    }

    // Method to run query to get number of values greater/lesser than or equal to the given value
    bool runQueryOp( T val, int op, int expected){
      return (range.getVal(val, op) == expected);
    }

    //Method to clear the data-set
    void clear(){
      range.clear();
    }

    // Range Query Algorithm
    RangeQuery<T> range;
};

/*
  This is a derived test suite class to test User-defined type data-set
*/
class UserTypeTestSuite : public TestSuite<userType>{
  public:
    UserTypeTestSuite(){}
    int run(int size){
      std::vector<userType> vec(size, {"aa", 23});
      vec.resize(size/4);
      vec.resize(size/2, {"abc", -14});
      vec.resize(3*size/4, {"xyz", 46});
      vec.resize(size, {"hello", 29});
      build(vec);
      
      assert( runQuery( {"hey",1}, {"there",29}, size/4) == true);
      std::cout << "Test case 1 passed" << std::endl;
      assert( runQuery( {"how",-100}, {"are",100}, size) == true);
      std::cout << "Test case 2 passed" << std::endl;
      assert( runQuery( {"you",-14}, {"doing",23}, 0) == true);
      std::cout << "Test case 3 passed" << std::endl;
      assert( runQuery( {"This",10}, {"is",46}, size/2) == true);
      std::cout << "Test case 4 passed" << std::endl;
      assert( runQuery( {"great",14}, {"stuff",59}, 3*size/4) == true);
      std::cout << "Test case 5 passed" << std::endl;
      assert( runQueryOp({"xxx", 23}, GREATER, size/2) == true);
      std::cout << "Test case 6 passed" << std::endl;
      assert( runQueryOp({"program", 46}, LESSER, 3*size/4) == true);
      std::cout << "Test case 7 passed" << std::endl;
      assert( runQueryOp({"test", 29}, EQUAL, size/4) == true);
      std::cout << "Test case 8 passed" << std::endl;
      clear();
      return 0; 
    }
};

/*
  This is a derived test suite class to test integer data-set
*/
class IntTestSuite : public TestSuite<int>{
  public:
    IntTestSuite(){}
    int run(int size){
      std::vector<int> vec(size, 10);
      vec.resize(size/2); 
      vec.resize(3*size/4, 5);
      vec.resize(size, -20);

      build(vec);      
      assert(runQuery( 1, 11, 3*size/4) == true);
      std::cout << "Test case 1 passed" << std::endl;
      assert(runQuery( -23, 11, size) == true);
      std::cout << "Test case 2 passed" << std::endl;
      assert(runQuery( 11, -2, 0) == true);
      std::cout << "Test case 3 passed" << std::endl;
      assert(runQuery( -20, 10, size/4) == true);
      std::cout << "Test case 4 passed" << std::endl;
      assert(runQuery( 5, 11, size/2) == true);
      std::cout << "Test case 5 passed" << std::endl;
      assert(runQueryOp( 10, LESSER, size/2) == true);
      std::cout << "Test case 6 passed" << std::endl;
      assert(runQueryOp( 5, GREATER, size/2) == true);
      std::cout << "Test case 7 passed" << std::endl;
      assert(runQueryOp( -20, EQUAL, size/4) == true);
      std::cout << "Test case 8 passed" << std::endl;
      assert(runQueryOp( 6, EQUAL, 0) == true);
      std::cout << "Test case 9 passed" << std::endl;
      clear();
      // Null Vector
      std::vector<int> vec2;
      build(vec2);
      assert(runQuery( -20, 10, 0) == true);
      std::cout << "Test case 10 passed" << std::endl;
      clear();
      return 0;
    }
};

/*
  This is a derived test suite class to test float data-set
*/
class FloatTestSuite : public TestSuite<float>{
  public:
    FloatTestSuite(){}

    int run(int size){
      std::vector<float> vec(size, 5.5);
      vec.resize(size/2);
      vec.resize(3*size/4, -1.2);
      vec.resize(size, 1234.67);
      build(vec);

      assert( runQuery( -2.3, 1235.23, size) == true);
      std::cout << "Test case 1 passed" << std::endl;
      assert( runQuery( 0, 10, size/2) == true);
      std::cout << "Test case 2 passed" << std::endl;
      assert( runQuery( -1.2, 1235.23, 3*size/4) == true);
      std::cout << "Test case 3 passed" << std::endl;
      assert( runQuery( 5.5, 1234, 0) == true);
      std::cout << "Test case 4 passed" << std::endl;
      assert( runQuery( 5.4, 123, size/2) == true);
      std::cout << "Test case 5 passed" << std::endl;
      assert(runQueryOp( -1.2, GREATER, 3*size/4) == true);
      std::cout << "Test case 6 passed" << std::endl;
      assert(runQueryOp( 0, LESSER, size/4) == true);
      std::cout << "Test case 7 passed" << std::endl;
      assert(runQueryOp( 5.5, EQUAL, size/2) == true);
      std::cout << "Test case 8 passed" << std::endl;
      clear();
      return 0;
    }
};

/*
  This is a derived test suite class to test String data-set
*/
class StringTestSuite : public TestSuite<std::string>{
  public:
    StringTestSuite(){}
    int run(int size){
      std::vector<std::string> vec(size, "nm");
      vec.resize(size/2);
      vec.resize(3*size/4, "abc");
      vec.resize(size, "zz");

      build(vec);
      assert( runQuery( "aaa", "xyz", 3*size/4) == true);
      std::cout << "Test case 1 passed" << std::endl;
      assert( runQuery( "nnn", "dcb", 0) == true);
      std::cout << "Test case 2 passed" << std::endl;
      assert( runQuery( "123aa", "zzz", size) == true);
      std::cout << "Test case 3 passed" << std::endl;
      assert( runQuery( "abc", "pq", size/2) == true);
      std::cout << "Test case 4 passed" << std::endl;
      assert( runQuery( "hello", "there", size/2) == true);
      std::cout << "Test case 5 passed" << std::endl;
      assert(runQueryOp( "abc", GREATER, 3*size/4) == true);
      std::cout << "Test case 6 passed" << std::endl;
      assert(runQueryOp( "this", LESSER, 3*size/4) == true);
      std::cout << "Test case 7 passed" << std::endl;
      assert(runQueryOp( "zz", EQUAL, size/4) == true);
      std::cout << "Test case 8 passed" << std::endl;
      clear();
      return 0;
    }
};

/* 
  Main Function 
  Can vary the size of the input data-set by changing the argument passes to the run method. 100,000 is the currently used size for all the types
*/
int main(){
  UserTypeTestSuite testUserType;
  if( testUserType.run(100000) == 0)
    std::cout << "\nTesting User-defined type: Success\n" << std::endl;
  else
    std::cout << "\nTesting User-defined type: Failed\n" << std::endl;

  IntTestSuite testInt;
  if( testInt.run(100000) == 0)
    std::cout << "\nTesting Integers: Success\n" << std::endl;
  else
    std::cout << "\nTesting Integers: Failed\n" << std::endl;
  
  FloatTestSuite testFloat;
  if( testFloat.run(100000) == 0)
    std::cout << "\nTesting Float: Success\n" << std::endl;
  else
    std::cout << "\nTesting Float: Failed\n" << std::endl;
  
  StringTestSuite testString;
  if( testString.run(100000) == 0)
    std::cout << "\nTesting String: Success\n" << std::endl;
  else
    std::cout << "\nTesting String: Failed\n" << std::endl;
} 
