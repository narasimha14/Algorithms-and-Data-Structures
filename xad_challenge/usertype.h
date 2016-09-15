/*
  @author: Narasimha Murthy
  This is a user defined data type defined using struct.
  @param str : A string type
  @param value : An int type data used as the value to compare while obtaining the range
*/
struct userType{
  userType() : str(""), value(0){}
  userType(std::string s, int val) : str(s), value(val){}
  std::string str;
  int value;
};

