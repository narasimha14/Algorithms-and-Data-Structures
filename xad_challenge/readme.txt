*************************
Problem statement:
*************************

Implement a program in C or C++ that does the following: 
Given a list of objects, we would like to know the number of objects that lies in a range of values. 
The list of objects doesn't change after the first time (i.e no objects are added, removed or changed. Hence you should optimize the data structure for reads and not worry about updates). 
For example: Assume the list of objects are random 10 million integers. An example query might be like "get number of objects >1000" or "get number of objects >10000 and <120000” 
or "get number of objects = 1000”. The objects should have a comparison operator defined.

Write few test cases with different types of objects(integers, floats, strings, user defined data type) of lengths from 10K to 100M, and print out the time taken (in microseconds) for few sample representative queries. 

*************************
Program Description:
*************************

This is a program that takes a list of objects as inputs and finds the number of objects in a range of interval or greater/lesser than or equal to the given object value.

*************************
Algorithm Used:
*************************

	The algorithm used was a simple sort and search. Basically given any input data-set, we sort it and then do a binary search on the sorted data to find the index of the given value(s) in the sorted data. Once we have the indices, it is trivial to find the number of objects that are present between those indices. 

Complexity: 
-----------
	Sorting takes O(nlogn) time. Space complexity is O(n) since we need to store the sorted input data. Once we build these sorted input data, the query time is O(logn). Here, n is the total number of objects.

	There is another way to do this. We can use a Splay tree or any self-balacing Binary Search Tree and augment each node with the subtree sizes and find the range. But the complexity still remains the same. There are various fancier data structures available to do this faster like Van Emde Boas or y-fast trees but they are overkill for this specific problem. 

************************
Files:
************************

range_query.h : 
	This header file contains the implementation of the algorithm mentioned above.
compare.h : 
	This header file contains the comparator functions defined for both user-defined data types and other data types such as int, float, string, etc.
user_type.h : 
	This header file contains the declaration & definition of user-defined data types. In my example, I've used a struct of a string and an int. Comparison is done based on the integer value. 
test_suite.cpp : 
	This is the main file and it exhibits Polymorphism. It has implementations of all the test suites for different data types. It has methods to run the required queries. There is an abstract base class with a pure virtual function called "run" that needs to be implemented by all the derived classes. There are separate derived classes for each data type.

************************
Execution:
************************
There is a Makefile that compiles and runs the code. Just run it using "make". If it needs to be run another time, you can either use "make" or it can be run by using the executable file 'run' on CLI using "./run"

************************
About the Makefile:
************************
Makefile is written to compile the files using g++ compiler. It has -Wall and -Weffc++ flags enabled, which displays all the warnings including the warnings for constructs that violate the guidelines in Scott Meyer's Effective C++.
Running "make clean" removes the executables created and also the temporary files. 

************************
Memory Limitations
************************
Testing the types with greater sizes may result in a bad alloc as the system could run out of memory eventually killing the process. On my system, I was able to successfully execute sizes of 100M for int, float and string. But for a user-defined type of a struct of string and int, I was only able to reach 60M. 
