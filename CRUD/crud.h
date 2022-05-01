#ifndef CRUD_H
#define CRUD_H

#include "../parser/parser.h"

#include <unordered_map>
#include <string>
#include <fstream>
#include <iostream>

namespace myDB {

  template <class DB, class hash>
  class CRUD
  {
  public:
    virtual std::string pars(const std::vector<std::string>&) = 0;
    void read_created_DBs();
    void generate_DB(const DB& db);
    virtual ~CRUD() = 0;
  public:
    void open_file_input(std::ifstream&, const std::string&);
    void push_db_name_in_sfile(const std::string&);
    void delete_db_name_in_sfile(const std::string&);
  protected:
    std::unordered_map<std::string, DB, hash> dbs;
  };

  template <class DB, class hash>
  class Creat : public CRUD<DB, hash>
  {
  public:
    virtual std::string pars(const std::vector<std::string>&);
    void creat_DB(const std::string&);
    void creat_DB(const std::string&, const std::vector<std::string>&);
    void push_info(const std::string&, const std::string&, const std::string&);
    void set_table(const std::string&, const std::vector<std::string>&);
  private: 

  };

  template <class DB, class hash>
  class Read : public CRUD<DB, hash>
  {
  public:
    virtual std::string pars(const std::vector<std::string>&);
    std::string get_table(const std::string&,const std::string&) const;
    std::string get_info(const std::string&, const std::string&, int) const; 
    std::string get_DB(const std::string&) const;
  };

  template <class DB, class hash>
  class Update : public CRUD<DB, hash>
  {
  public:
    virtual std::string pars(const std::vector<std::string>&);
    void change_info(const std::string&, const std::string&, int, const std::string&);
  };

  template <class DB, class hash>
  class Delete : public CRUD<DB, hash>
  {
  public:
    virtual std::string pars(const std::vector<std::string>&);
    void delete_table(const std::string&, const std::string&);
    void delete_info(const std::string&, const std::string&, int);
    void delete_DB(const std::string&);
  };

} // myDB

template <class DB, class hash>
myDB::CRUD<DB,hash>::~CRUD()
{}

template <class DB, class hash>
std::string myDB::Creat<DB,hash>::pars(const std::vector<std::string>& tokens)
{
  if(tokens.at(0) == "creat") {
    creat_DB(tokens.at(1));
    return "ok\n";
  } else if(tokens.at(0) == "creat_DB_tables") {
    creat_DB(tokens.at(1), std::vector<std::string>(tokens.begin() + 2, tokens.end()));
    return "ok\n";
  } else if(tokens.at(0) == "creat_table") {
    set_table(tokens.at(1),std::vector<std::string>(tokens.begin() + 2, tokens.end()));
    return "ok\n";
  } else if(tokens.at(0) == "creat_info") {
    push_info(tokens.at(1), tokens.at(2), tokens.at(3));
    return "ok\n";
  }
  return "error sxal creat-i hraman\n";
}

template <class DB, class hash>
std::string myDB::Read<DB,hash>::pars(const std::vector<std::string>& tokens)
{
  if(tokens.at(0) == "read") {
    get_DB(tokens.at(1));
    return "ok\n";
  } else if(tokens.at(0) == "read_table") {
    get_table(tokens.at(1), tokens.at(2));
    return "ok\n";
  } else if(tokens.at(0) == "read_info") {
    get_info(tokens.at(1),tokens.at(2), std::stoi(tokens.at(3)));
    return "ok\n";
  } 
  return "error sxal read-i hraman\n";
}

template <class DB, class hash>
std::string myDB::Update<DB,hash>::pars(const std::vector<std::string>& tokens)
{
  if(tokens.at(0) == "update") {
    change_info(tokens.at(1), tokens.at(2), std::stoi(tokens.at(3)), tokens.at(4));
    return "ok\n";
  } 
  return "error sxal update-i hraman\n";
}

template <class DB, class hash>
std::string myDB::Delete<DB,hash>::pars(const std::vector<std::string>& tokens)
{
  if(tokens.at(0) == "delete") {
    delete_DB(tokens.at(1));
    system(("rm ./DataBaseTxt/" + tokens.at(1)).c_str());
    return "ok\n";
  } else if(tokens.at(0) == "delete_table") {
    delete_table(tokens.at(1), tokens.at(2));
    return "ok\n";
  } else if(tokens.at(0) == "delete_info") {
    delete_info(tokens.at(1), tokens.at(2), std::stoi(tokens.at(3)));
    return "ok\n";
  } 
  return "error sxal delete-i hraman\n";
}

template <class DB, class hash>
void myDB::CRUD<DB,hash>::generate_DB(const DB& db)
{
  std::ofstream ofile;
  ofile.open("./DataBaseTxt/" + db.get_DataBase_name());
  ofile << db.get_DB();
  ofile.close();
}

template <class DB, class hash>
void myDB::CRUD<DB,hash>::read_created_DBs()
{
  std::vector<std::string> files_names;
  std::ifstream ifile;
  open_file_input(ifile, "./.DBnames/names.txt");
  std::string file_name;

  while(!ifile.eof())
  {
    file_name.clear();
    ifile >> file_name;
    files_names.push_back(file_name);
  }
  
  ifile.close();
  file_name = "./DataBaseTxt/";
  std::string str;
  Parser pars;

  for(int i {}; i < files_names.size() - 1; ++i)
  {
    open_file_input(ifile, file_name + files_names[i]);
    DB tmp_db_obj(files_names[i]);
    while(!ifile.eof())
    {
      std::getline(ifile, str);
      pars.parse_code(str);
      std::vector<std::string> tokens = pars.get_tokens();
      if(!tokens.empty())
      {
        tmp_db_obj.set_table(tokens[0]);

        for(int j = 2; j < tokens.size(); ++j)
        {
          tmp_db_obj.set_info(tokens[0], j - 2, tokens[j]);
        }
      }
    }
    dbs.emplace(tmp_db_obj.get_DataBase_name(),tmp_db_obj);
    ifile.close();
  }
}

template <class DB, class hash>
void myDB::CRUD<DB,hash>::delete_db_name_in_sfile(const std::string& db_name)
{
  std::vector<std::string> names;
  std::ifstream ifile;
  open_file_input(ifile, "./.DBnames/names.txt");

  std::string str;
  while(!ifile.eof())
  {
    str.clear();
    ifile >> str;
    if(str != db_name && !str.empty()) 
      names.push_back(str);
  }

  ifile.close();
  std::ofstream ofile;
  ofile.open("./.DBnames/names.txt");

  for(const auto& name: names)
    ofile << name << std::endl;
  ofile.close();
}

template <class DB, class hash>
void myDB::CRUD<DB,hash>::push_db_name_in_sfile(const std::string& db_name)
{
  std::ifstream ifile;
  open_file_input(ifile, "./.DBnames/names.txt");
  std::string str;
  while(!ifile.eof())
  {
    ifile >> str;
    if(str == db_name) return;
  }
  ifile.close();

  std::ofstream ofile;
  ofile.open("./.DBnames/names.txt", std::ios::app);
  ofile << db_name << std::endl;
  ofile.close();
}

template <class DB, class hash>
void myDB::CRUD<DB,hash>::open_file_input(std::ifstream& ifile, const std::string& fileName)
{
  ifile.open(fileName);

  if(!ifile.is_open()) {
    std::cerr << fileName << std::endl;
    std::cerr << "file is not open" << std::endl;
    exit(0);
  }
}

template <class DB, class hash>
void myDB::Creat<DB,hash>::set_table(const std::string& DB_name, const std::vector<std::string>& table_names)
{
  auto& db = this->dbs.at(DB_name);
  for(const auto& t_name: table_names)
  {
    db.set_table(t_name);
  }
  CRUD<DB,hash>::generate_DB(db);
}

template <class DB, class hash>
void myDB::Creat<DB,hash>::creat_DB(const std::string& DB_name,const std::vector<std::string>& tables)
{
  DB db(DB_name, tables);
  this->dbs.emplace(DB_name, db);
  CRUD<DB,hash>::push_db_name_in_sfile(DB_name);
  CRUD<DB,hash>::generate_DB(db);
}

template <class DB, class hash>
void myDB::Creat<DB,hash>::creat_DB(const std::string& DB_name)
{
  DB db(DB_name);
  this->dbs.emplace(DB_name, db);
  CRUD<DB,hash>::push_db_name_in_sfile(DB_name);
  CRUD<DB,hash>::generate_DB(db);
}

template <class DB, class hash>
void myDB::Creat<DB,hash>::push_info(const std::string& DB_name, const std::string& table_name, const std::string& info)
{
  auto &db = this->dbs.at(DB_name);
  db.set_info(table_name, db.get_table_size(table_name), info);
  CRUD<DB,hash>::generate_DB(db);
}

template <class DB, class hash>
std::string myDB::Read<DB,hash>::get_DB(const std::string& DB_name) const
{
  auto &db = this->dbs.at(DB_name);
  return db.get_DB();
}

template <class DB, class hash>
std::string myDB::Read<DB,hash>::get_info(const std::string& DB_name, const std::string& table_name, int count) const
{
  auto &db = this->dbs.at(DB_name);
  return db.get_info(table_name, count);
}

template <class DB, class hash>
std::string myDB::Read<DB,hash>::get_table(const std::string& DB_name, const std::string& table_name) const
{
  auto &db = this->dbs.at(DB_name);
  return db.get_table(table_name);
}

template <class DB, class hash>
void myDB::Update<DB,hash>::change_info(const std::string& DB_name, const std::string& table_name, int count, const std::string& info)
{
  auto &db = this->dbs.at(DB_name);
  db.change_info(table_name, count, info);
  CRUD<DB,hash>::generate_DB(db);
}

template <class DB, class hash>
void myDB::Delete<DB,hash>::delete_table(const std::string& DB_name, const std::string& table_name)
{
  auto &db = this->dbs.at(DB_name);
  db.delete_table(table_name);
  CRUD<DB,hash>::generate_DB(db);
}

template <class DB, class hash>
void myDB::Delete<DB,hash>::delete_info(const std::string& DB_name, const std::string& table_name, int count)
{
  auto &db = this->dbs.at(DB_name);
  db.delete_info(table_name, count);
  CRUD<DB,hash>::generate_DB(db);
}

template <class DB, class hash>
void myDB::Delete<DB,hash>::delete_DB(const std::string& DB_name) 
{
  this->dbs.erase(DB_name);
  this->delete_db_name_in_sfile(DB_name);
}

#endif // CRUD_H