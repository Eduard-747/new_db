#include "DataBase.h"

int myDB::DataBase::get_table_size(const std::string & table_name) const
{
  return table.at(table_name).size();
}

bool myDB::DataBase::operator==(const DataBase& r) const
{
  return this->name == r.name;
}

myDB::DataBase::DataBase(const std::string& DB_name)
{
  name = DB_name;
}

myDB::DataBase::DataBase(const std::string& DB_name,const std::vector<std::string>& table_names)
{
  name = DB_name;
  
  for(const auto& tableName: table_names) 
  {
    table.emplace(tableName, std::map<int,std::string>{});
  }
}

std::string myDB::DataBase::get_table(const std::string& table_name) const
{
  std::string table_info;

  for(auto j: table.find(table_name)->second)
  {
    table_info += j.second;
  }
  
  return table_info;
}

std::string myDB::DataBase::get_DataBase_name() const
{
  return name;
}

void myDB::DataBase::set_info(const std::string& table_name,int count, const std::string& info)
{
  table.at(table_name).emplace(count,info);
}

void myDB::DataBase::change_info(const std::string& table_name, int count, const std::string& new_info)
{
  table.at(table_name).at(count) = new_info;
}

void myDB::DataBase::delete_table(const std::string& table_name)
{
  table.erase(table_name);
}

void myDB::DataBase::delete_info(const std::string& table_name, int count)
{
  table.at(table_name).erase(count);
}

std::string myDB::DataBase::get_info(const std::string& table_name, int count) const
{
  return table.at(table_name).at(count);
}

void myDB::DataBase::delete_DB()
{
  table.clear();
  name.clear();
}

void myDB::DataBase::set_table(const std::string& table_name)
{
  table.emplace(table_name, std::map<int,std::string>{}); 
}

std::string myDB::DataBase::get_DB() const
{
  std::string DB_look;
  for(const auto& i: table)
  {
    DB_look += i.first + " - ";
    for(const auto& j: i.second)
    {
      DB_look += j.second + " ";
    }
    DB_look.push_back('\n');
    
  }
  
  return DB_look;
}