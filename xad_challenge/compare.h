/*
  @author: Narasimha Murthy
  This is a functor that overloads the '()' operator.
  This is used as a comparator for sorting
  @tparam T :  A list of data types
*/
template<typename T>
class compare{
    public:
      /*
        Overloaded method for the bracket operator
        @tparam T
        @arg left : Left operand of type T
        @arg right : Right operand of type T
      */
      bool operator()(const T& left, const T& right){
       return comparator<T>(left, right);
      }
    private:
      /*
        This is a comparator method that will be called only if the data type of the arguments are the user-defined types i.e. userType in this case
        @tparam U : User-defined type
        @arg left : Left operand of type U
        @arg right : Right operand of type U
      */
      template<class U>
      typename std::enable_if< std::is_same<U, userType>::value, bool >::type
      comparator(const U& left,const U& right){
        return left.value < right.value;
      }
      /*
        This is a comparator method that will be called for all other argument types other than the user-defined type such as int, float, string, etc.
        @tparam U : int/float/string
        @arg left : Left operand of type U
        @arg right : Right operand of type U
      */
      template<class U>
      typename std::enable_if< std::is_same<U, int>::value || std::is_same<U, float>::value || std::is_same<U, std::string>::value, bool >::type
      comparator(const U& left, const U& right){
        return left < right;
      }
};

