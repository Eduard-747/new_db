#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <map>

namespace myDB {

  class DataBase
  {
  public:
    DataBase(const std::string&);
    DataBase(const std::string&, const std::vector<std::string>&);

    std::string get_DataBase_name() const; 
    std::string get_table(const std::string&) const; 
    std::string get_info(const std::string&, int) const; 
    std::string get_DB() const; 

    void set_table(const std::string&); 
    void set_info(const std::string&, int, const std::string&); 
    void change_info(const std::string&, int, const std::string&); 

    void delete_table(const std::string&); 
    void delete_info(const std::string&, int); 
    void delete_DB(); 
    int get_table_size(const std::string&) const;

    bool operator==(const DataBase&) const;

  private:
    std::string name;
    std::unordered_map<std::string, std::map<int,std::string>> table;
  };

} // myDB

#endif // DATABASE_H