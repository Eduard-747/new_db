#include "command.h"

#include <vector>
#include <string>
#include <iostream>

size_t myDB::mhash::operator()(const myDB::DataBase& o) const
{
  return std::hash<std::string>{}(o.get_DataBase_name());
}

std::string myDB::Command::_creat(const std::vector<std::string>& tokens)
{
  myDB::CRUD<myDB::DataBase, myDB::mhash> * crud = new myDB::Creat<myDB::DataBase, myDB::mhash>;
  try
  {
    crud->read_created_DBs();
    std::string message = crud->pars(tokens);
    delete crud;
    return message;
  }
  catch(const std::exception& e)
  {
    delete crud;
    return "creat-i sxal hraman\n";
  }
}

std::string myDB::Command::_read(const std::vector<std::string>& tokens) 
{
  myDB::CRUD<myDB::DataBase, myDB::mhash> * crud = new myDB::Read<myDB::DataBase, myDB::mhash>;
  try
  {
    crud->read_created_DBs();
    std::string message = crud->pars(tokens);
    delete crud;
    return message;
  }
  catch(const std::exception& e)
  {
    delete crud;
    return "read-i sxal hraman\n";
  }
}

std::string myDB::Command::_update(const std::vector<std::string>& tokens)
{
  myDB::CRUD<myDB::DataBase, myDB::mhash> * crud = new myDB::Update<myDB::DataBase, myDB::mhash>;
  try
  {
    crud->read_created_DBs();
    std::string message = crud->pars(tokens);
    delete crud;
    return message;
  }
  catch(const std::exception& e)
  {
    delete crud;
    return "update-i sxal hraman\n";
  }
}

std::string myDB::Command::_delete(const std::vector<std::string>& tokens)
{
  myDB::CRUD<myDB::DataBase, myDB::mhash> * crud = new myDB::Delete<myDB::DataBase, myDB::mhash>;
  try
  {
    crud->read_created_DBs();
    std::string message = crud->pars(tokens);
    delete crud;
    return message;
  }
  catch(const std::exception& e)
  {
    delete crud;
    return "delete-i sxal hraman\n";
  }
}


std::string myDB::Command::_disconnect(const std::vector<std::string>& tokens)
{
  return "thank you\n";
}

myDB::Command::Command()
{
  com_coll["creat"] = &Command::_creat;
  com_coll["creat_DB_tables"] = &Command::_creat;
  com_coll["creat_table"] = &Command::_creat;
  com_coll["creat_info"] = &Command::_creat;

  com_coll["read"] = &Command::_read;
  com_coll["read_table"] = &Command::_read;
  com_coll["read_info"] = &Command::_read;

  com_coll["update"] = &Command::_update;

  com_coll["delete"] = &Command::_delete;
  com_coll["delete_table"] = &Command::_delete;
  com_coll["delete_info"] = &Command::_delete;

  com_coll["disconnect"] = &Command::_disconnect;
}

std::string myDB::Command::coll_command(const std::vector<std::string>& tokens)
{
  try
  {
    return (this->*com_coll.at(tokens[0]))(tokens);
  }
  catch(const std::exception& e)
  {
    return "aydpisi hraman chka\n";
  }
}