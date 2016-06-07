#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <climits>
#include <set>
using namespace std;

/**
 *
 * @author: Narasimha Murthy
 * Implement SQL type functions
 *
 *
 **/


class Table {
  public:
    Table(const string& name, const vector<string>& column_names, const vector<vector<string> > data) : name_(name), column_names_(column_names), data_(data) {}

    const string& name() const { return name_; }
    const vector<string>& column_names() const { return column_names_; }
    const vector<vector<string> >& data() const { return data_; }

    // Callee will own the returned pointer
    Table* Select(const vector<string>& column_names) const {
      // IMPLEMENT ME
      vector<int> reqd;
      vector<string> col;
      for(int j=0; j < column_names.size(); ++j){
        for(int i=0; i<column_names_.size(); ++i){
          if(column_names[j] == column_names_[i]){
            reqd.push_back(i);
          }
        }
      }
      vector<vector<string> > out;
      for(int i=0; i<data_.size();++i){
        vector<string> out2;
        for(int j=0; j <reqd.size();++j){
          out2.push_back(data_[i][reqd[j]]);

        }
        if(out2.size() != 0)
          out.push_back(out2);
      }
      return new Table("Select", column_names, out);
    }

    // Callee will own the returned pointer
    Table* Where(const string& column_name, const string& value) const {
      // IMPLEMENT ME
      int idx = 0;
      for(int i=0; i< column_names_.size(); ++i){
        if(column_names_[i] == column_name){
          idx = i;
          break;
        }
      }
      vector< vector<string> > out;
      for(int j=0; j< data_.size(); ++j){
        vector<string> out2;
        if(data_[j][idx] == value){
          for(int i=0; i < data_[j].size(); ++i){
            out2.push_back(data_[j][i]);
          }
        }
        if(out2.size() != 0)
          out.push_back(out2);
      }
      return new Table("WhereTable", column_names_, out);
    }

    void Print() {
      string output = JoinStringVector(column_names_);
      output += "\n";
      for (size_t row_index = 0; row_index < data_.size(); ++row_index) {
        output += JoinStringVector(data_[row_index]);
        output += "\n";
      }
      cout << output << endl;
    }

  private:
    string JoinStringVector(const vector<string>& input) {
      string output = "";
      bool has_data = false;
      for (size_t i = 0; i < input.size(); ++i) {
        has_data = true;
        output += input[i];
        output += ", ";
      }
      if (has_data) {
        output = output.substr(0, output.length() - 2);
      }
      return output;
    }
    const string name_;
    const vector<string> column_names_;
    const vector<vector<string> > data_; // only support string type for simplicity
};


class Database {
  public:
    Database(map<string, const Table*> table_map) : table_map_(table_map) {}
    ~Database() {
      for(map<string, const Table*>::iterator iterator = table_map_.begin(); iterator != table_map_.end(); ++iterator) {
        delete iterator->second;
      }
    }

    const Table* GetTable(const string& table_name) { return table_map_[table_name]; }

    // Callee will own the returned pointer
    /* 
       Table* InnerJoin(
       const Table* left_table, const string& left_table_key_name,
       const Table* right_table, const string& right_table_key_name) {

    // IMPLEMENT ME
    vector<string> lefttable_columns;
    lefttable_columns = left_table->column_names();
    vector< vector<string> > left_data;
    left_data= left_table->data();
    vector<string> righttable_columns;
    righttable_columns = right_table->column_names();
    vector< vector<string> > right_data;
    right_data= right_table->data();

    int idx_left, idx_right;
    for( int i =0; lefttable_columns.size(); ++i){
    if(left_table_key_name == lefttable_columns[i]){
    idx_left = i;
    break;
    }
    }
    for( int i =0; righttable_columns.size(); ++i){
    if(right_table_key_name == righttable_columns[i]){
    idx_right = i;
    break;
    }
    }

    vector<string> out;
    vector< vector<string> > out2;
    out.push_back("users.name");
    out.push_back("departments.name");
    int idx_name_l, idx_name_r;
    for(int i=0; i< lefttable_columns.size(); ++i)
    {
    if(lefttable_columns[i] == "name"){
    idx_name_l = i;
    break;
    }
    }
    for(int i=0; i< righttable_columns.size(); ++i)
    {
    if(righttable_columns[i] == "name"){
    idx_name_r = i;
    break;
    }
    }

    for(int i =0; i < left_data.size(); ++i){
    vector<string> out3;
    out3.push_back(left_data[i][idx_name_l]);
    for(int j=0; j < right_data.size(); ++j){
    if(right_data[j][idx_right] == left_data[i][idx_left]){
    out3.push_back(right_data[j][idx_name_r]);
    }
    }
    if(out3.size() != 0)
    out2.push_back(out3);

    }
    return new Table("InnerJoin", out, out2);
    }
    */

    Table* InnerJoin(
        const Table* left_table, const string& left_table_key_name,
        const Table* right_table, const string& right_table_key_name) {
      vector<string> left_columns = left_table->column_names();
      vector<string> right_columns = right_table->column_names();

      int idx_left, idx_right;
      vector<string> out2, columns;
      for(int i=0; i < left_columns.size(); ++i){
        columns.push_back(left_table->name()+"."+left_columns[i]);
        if(left_columns[i] == left_table_key_name){
          idx_left = i;
        }
      }
      for(int i=0; i < right_columns.size(); ++i){
        columns.push_back(right_table->name()+"."+right_columns[i]);
        if(right_columns[i] == right_table_key_name){
          idx_right = i;
        }
      }
      vector<vector<string> > left_data = left_table->data();
      vector<vector<string> > right_data = right_table->data();
      vector<vector<string> > out;
      for(int i=0; i < left_data.size(); ++i){
        for(int j=0; j < right_data.size(); ++j){
          if(left_data[i][idx_left] == right_data[j][idx_right]){
            for(int k=0; k < left_columns.size(); ++k){
              out2.push_back(left_data[i][k]);
            }
            for(int k=0; k < right_columns.size(); ++k){
              out2.push_back(right_data[j][k]);
            }
            out.push_back(out2);
            out2.clear();
          }
        }
      }

      return new Table("InnerJoin", columns, out);
    }



    // Callee will own the returned pointer
    /*
       Table* LeftJoin(
       const Table* left_table, const string& left_table_key_name,
       const Table* right_table, const string& right_table_key_name) {
// IMPLEMENT ME
vector<string> lefttable_columns;
lefttable_columns = left_table->column_names();
vector< vector<string> > left_data;
left_data= left_table->data();
vector<string> righttable_columns;
righttable_columns = right_table->column_names();
vector< vector<string> > right_data;
right_data= right_table->data();

int idx_left, idx_right;
for( int i =0; lefttable_columns.size(); ++i){
if(left_table_key_name == lefttable_columns[i]){
idx_left = i;
break;
}
}
for( int i =0; righttable_columns.size(); ++i){
if(right_table_key_name == righttable_columns[i]){
idx_right = i;
break;
}
}

vector<string> out;
vector< vector<string> > out2;
out.push_back("users.name");
out.push_back("salaries.amount");
int idx_name_l, idx_name_r;
for(int i=0; i< lefttable_columns.size(); ++i)
{
if(lefttable_columns[i] == "name"){
idx_name_l = i;
break;
}
}
for(int i=0; i< righttable_columns.size(); ++i)
{
if(righttable_columns[i] == "amount"){
idx_name_r = i;
break;
}
}
set<string> set_left;
set<string> set_right;
for(int i =0; i < left_data.size(); ++i){
set_left.insert(left_data[i][idx_left]);
for(int j=0; j < right_data.size(); ++j){
set_right.insert(right_data[j][idx_right]);
vector<string> out3;
if(right_data[j][idx_right] == left_data[i][idx_left]){
out3.push_back(left_data[i][idx_name_l]);
out3.push_back(right_data[j][idx_name_r]);
}
if(out3.size() != 0)
out2.push_back(out3);
}

}
set<string>::iterator it;
vector<string> out3;
for(int i=0; i< left_data.size(); ++i){
it = set_right.find(left_data[i][idx_left]);
if(it == set_right.end() ){
out3.push_back(left_data[i][idx_name_l]);
out3.push_back("");
out2.push_back(out3);
}
}
return new Table("LeftJoin", out, out2);
}
*/

Table* LeftJoin(
    const Table* left_table, const string& left_table_key_name,
    const Table* right_table, const string& right_table_key_name) {

  vector<string> left_columns = left_table->column_names();
  vector<string> right_columns = right_table->column_names();

  int idx_left, idx_right;
  vector<string> out2, columns;
  for(int i=0; i < left_columns.size(); ++i){
    columns.push_back(left_table->name()+"."+left_columns[i]);
    if(left_columns[i] == left_table_key_name){
      idx_left = i;
    }
  }
  for(int i=0; i < right_columns.size(); ++i){
    columns.push_back(right_table->name()+"."+right_columns[i]);
    if(right_columns[i] == right_table_key_name){
      idx_right = i;
    }
  }

  vector<vector<string> > left_data = left_table->data();
  vector<vector<string> > right_data = right_table->data();
  vector<vector<string> > out;
  vector<bool> set(left_data.size(), false);
  for(int i=0; i < left_data.size();++i){
    for(int j=0; j < right_data.size(); ++j){
      if(left_data[i][idx_left] == right_data[j][idx_right]){
        set[i] = true;
        for(int k=0; k < left_data[i].size(); ++k){
          out2.push_back(left_data[i][k]);
        }
        for(int k=0; k < right_data[j].size(); ++k){
          out2.push_back(right_data[j][k]);
        }
        out.push_back(out2);
        out2.clear();
      }
    }
  }

  for(int i=0; i < set.size(); ++i){
    if(!set[i]){
      for(int k=0; k < left_data[i].size(); ++k){
        out2.push_back(left_data[i][k]);
      }
      for(int k=0;k < right_columns.size();++k){
        out2.push_back("");
      }
      out.push_back(out2);   
    }
  } 
  return new Table("LeftJoin", columns, out);

}


/*Table* RightJoin(
  const Table* left_table, const string& left_table_key_name,
  const Table* right_table, const string& right_table_key_name) {
// IMPLEMENT ME
vector<string> lefttable_columns;
lefttable_columns = left_table->column_names();
vector< vector<string> > left_data;
left_data= left_table->data();
vector<string> righttable_columns;
righttable_columns = right_table->column_names();
vector< vector<string> > right_data;
right_data= right_table->data();

int idx_left, idx_right;
for( int i =0; lefttable_columns.size(); ++i){
if(left_table_key_name == lefttable_columns[i]){
idx_left = i;
break;
}
}
for( int i =0; righttable_columns.size(); ++i){
if(right_table_key_name == righttable_columns[i]){
idx_right = i;
break;
}
}

vector<string> out;
vector< vector<string> > out2;
out.push_back("users.name");
out.push_back("salaries.amount");
int idx_name_l, idx_name_r;
for(int i=0; i< lefttable_columns.size(); ++i)
{
if(lefttable_columns[i] == "name"){
idx_name_l = i;
break;
}
}
for(int i=0; i< righttable_columns.size(); ++i)
{
if(righttable_columns[i] == "amount"){
idx_name_r = i;
break;
}
}
set<string> set_left;
set<string> set_right;
for(int i =0; i < left_data.size(); ++i){
set_left.insert(left_data[i][idx_left]);
for(int j=0; j < right_data.size(); ++j){
set_right.insert(right_data[j][idx_right]);
vector<string> out3;
if(right_data[j][idx_right] == left_data[i][idx_left]){
out3.push_back(left_data[i][idx_name_l]);
out3.push_back(right_data[j][idx_name_r]);
}
if(out3.size() != 0)
out2.push_back(out3);
}

}
set<string>::iterator it;
vector<string> out3;
for(int i=0; i< right_data.size(); ++i){
it = set_left.find(right_data[i][idx_right]);
if(it == set_left.end() ){
out3.push_back("");
out3.push_back(right_data[i][idx_name_r]);
out2.push_back(out3);
}
}
return new Table("RightJoin", out, out2);
}
*/

Table* RightJoin(
    const Table* left_table, const string& left_table_key_name,
    const Table* right_table, const string& right_table_key_name) {

  vector<string> left_columns = left_table->column_names();
  vector<string> right_columns = right_table->column_names();

  int idx_left, idx_right;
  vector<string> out2, columns;
  for(int i=0; i < left_columns.size(); ++i){
    columns.push_back(left_table->name()+"."+left_columns[i]);
    if(left_columns[i] == left_table_key_name){
      idx_left = i;
    }
  }
  for(int i=0; i < right_columns.size(); ++i){
    columns.push_back(right_table->name()+"."+right_columns[i]);
    if(right_columns[i] == right_table_key_name){
      idx_right = i;
    }
  }

  vector<vector<string> > left_data = left_table->data();
  vector<vector<string> > right_data = right_table->data();
  vector<vector<string> > out;
  vector<bool> set(right_data.size(), false);
  for(int i=0; i < right_data.size();++i){
    for(int j=0; j < left_data.size(); ++j){
      if(right_data[i][idx_right] == left_data[j][idx_left]){
        set[i] = true;
        for(int k=0; k < left_columns.size(); ++k){
          out2.push_back(left_data[j][k]);
        }
        for(int k=0; k < right_columns.size(); ++k){
          out2.push_back(right_data[i][k]);
        }
        out.push_back(out2);
        out2.clear();
      }
    }  
  }

  for(int i=0; i < set.size(); ++i){
    if(!set[i]){
      for(int k=0; k < left_columns.size(); ++k){
        out2.push_back("");
      }
      for(int k=0; k < right_columns.size(); ++k){
        out2.push_back(right_data[i][k]);
      }
      out.push_back(out2);
      out2.clear();
    }
  } 
  return new Table("RightJoin", columns, out); 
}

// Callee will own the returned pointer
/*
   Table* OuterJoin(
   const Table* left_table, const string& left_table_key_name,
   const Table* right_table, const string& right_table_key_name) {
// IMPLEMENT ME
vector<string> lefttable_columns;
lefttable_columns = left_table->column_names();
vector< vector<string> > left_data;
left_data= left_table->data();
vector<string> righttable_columns;
righttable_columns = right_table->column_names();
vector< vector<string> > right_data;
right_data= right_table->data();

int idx_left, idx_right;
for( int i =0; lefttable_columns.size(); ++i){
if(left_table_key_name == lefttable_columns[i]){
idx_left = i;
break;
}
}
for( int i =0; righttable_columns.size(); ++i){
if(right_table_key_name == righttable_columns[i]){
idx_right = i;
break;
}
}

vector<string> out;
vector< vector<string> > out2;
out.push_back("users.name");
out.push_back("salaries.amount");
int idx_name_l, idx_name_r;
for(int i=0; i< lefttable_columns.size(); ++i)
{
if(lefttable_columns[i] == "name"){
idx_name_l = i;
break;
}
}
for(int i=0; i< righttable_columns.size(); ++i)
{
if(righttable_columns[i] == "amount"){
idx_name_r = i;
break;
}
}
set<string> set_left;
set<string> set_right;
for(int i =0; i < left_data.size(); ++i){
set_left.insert(left_data[i][idx_left]);
for(int j=0; j < right_data.size(); ++j){
set_right.insert(right_data[j][idx_right]);
vector<string> out3;
if(right_data[j][idx_right] == left_data[i][idx_left]){
out3.push_back(left_data[i][idx_name_l]);
out3.push_back(right_data[j][idx_name_r]);
}
if(out3.size() != 0)
out2.push_back(out3);
}

}
set<string>::iterator it;
vector<string> out3;
for(int i=0; i< left_data.size(); ++i){
it = set_right.find(left_data[i][idx_left]);
if(it == set_right.end() ){
out3.push_back(left_data[i][idx_name_l]);
out3.push_back("");
out2.push_back(out3);
}
}
out3.clear();
for(int i=0; i< right_data.size(); ++i){
  it = set_left.find(right_data[i][idx_right]);
  if(it == set_left.end() ){
    out3.push_back("");
    out3.push_back(right_data[i][idx_name_r]);
    out2.push_back(out3);
  }
}
return new Table("OuterJoin", out, out2);
} 
*/

Table* OuterJoin(
    const Table* left_table, const string& left_table_key_name,
    const Table* right_table, const string& right_table_key_name) {

  Table *leftjoin = LeftJoin(left_table, left_table_key_name, right_table, right_table_key_name);
  Table *rightjoin = RightJoin(left_table, left_table_key_name, right_table, right_table_key_name);

  int right_columns_size = right_table->column_names().size();

  vector<vector<string> > left_data = leftjoin->data();
  vector<vector<string> > right_data = rightjoin->data();
  vector<vector<string> > out = left_data;
  for(int i=0; i < right_data.size(); ++i){
    bool append = true;
    for(int j=0; j < right_columns_size; ++j){
      if(right_data[i][j] != ""){
        append = false;
      }
    }
    if(append){
      out.push_back(right_data[i]);
    }
  }

  return new Table("OuterJoin", leftjoin->column_names(), out);
}

private:
map<string, const Table*> table_map_;
};

#ifndef __main__
#define __main__

int main(int argc, char* argv[]) {
  //vector<string> col1("id, "name");
  //vector<string> col2("0", "engineering");
  const Table* department_table = new Table(
      "departments",
      { "id", "name" },
      {
      { "0", "engineering" },
      { "1", "finance" }
      });

  const Table* user_table = new Table(
      "users",
      { "id", "department_id", "name" },
      {
      { "0", "0", "Ian" },
      { "1", "0", "John" },
      { "2", "1", "Eddie" },
      { "3", "1", "Mark" },
      });

  const Table* salary_table = new Table(
      "salaries",
      { "id", "user_id", "amount" },
      {
      { "0", "0", "100" },
      { "1", "1", "150" },
      { "2", "1", "200" },
      { "3", "3", "200" },
      { "4", "3", "300" },
      { "5", "4", "400" },
      });

  map<string, const Table*> table_map = map<string, const Table*>();
  table_map["departments"] = department_table;
  table_map["users"] = user_table;
  table_map["salaries"] = salary_table;
  Database* db = new Database(table_map);
  // should print
  // id, department_id, name
  // 1, 0, John
  {
    Table* filtered_table = db->GetTable("users")->Where("id", "1");
    Table* projected_table = filtered_table->Select({ "id", "department_id", "name" });
    projected_table->Print();
    delete projected_table;
    delete filtered_table;
  }
  // should print
  // users.name, departments.name
  // Ian, engineering
  // John, engineering
  {
    Table* table = db->InnerJoin(
        db->GetTable("users"),
        "department_id",
        db->GetTable("departments"),
        "id");
    Table* filtered_table = table->Where("departments.name", "engineering");
    Table* projected_table = filtered_table->Select({ "users.name", "departments.name" });
    projected_table->Print();
    delete projected_table;
    delete filtered_table;
    delete table;
  }

  // should print
  // users.name, salaries.amount
  // Ian, 100
  // John, 150
  // John, 200
  // Mark, 200
  // Mark, 300
  // Eddie,
  {
    Table* table = db->LeftJoin(
        db->GetTable("users"),
        "id",
        db->GetTable("salaries"),
        "user_id");
    Table* projected_table = table->Select({ "users.name", "salaries.amount" });
    projected_table->Print();
    delete projected_table;
    delete table;
  }

  // should print
  // users.name, salaries.amount
  // Ian, 100
  // John, 150
  // John, 200
  // Mark, 200
  // Mark, 300
  // , 400
  {
    Table* table = db->RightJoin(
        db->GetTable("users"),
        "id",
        db->GetTable("salaries"),
        "user_id");
    Table* projected_table = table->Select({ "users.name", "salaries.amount" });
    projected_table->Print();
    delete projected_table;
    delete table;
  }

  // should print
  // users.name, salaries.amount
  // Ian, 100
  // John, 150
  // John, 200
  // Mark, 200
  // Mark, 300
  // Eddie,
  // , 400
  {
    Table* table = db->OuterJoin(
        db->GetTable("users"),
        "id",
        db->GetTable("salaries"),
        "user_id");
    Table* projected_table = table->Select({ "users.name", "salaries.amount" });
    projected_table->Print();
    delete projected_table;
    delete table;
  }

  delete db;
}

#endif

