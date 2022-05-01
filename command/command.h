#ifndef COMMAND_H
#define COMMAND_H

#include "../CRUD/crud.h"
#include "../DataBase/DataBase.h"

#include <vector>
#include <unordered_map>

namespace myDB {
  class mhash
  {
  public:
    size_t operator()(const myDB::DataBase& o) const;
  };
  class Command
  {
  public:
    Command();

    std::string coll_command(const std::vector<std::string>&);

    std::string _creat(const std::vector<std::string>&);

    std::string _read(const std::vector<std::string>&);

    std::string _update(const std::vector<std::string>&);

    std::string _delete(const std::vector<std::string>&);

    std::string _disconnect(const std::vector<std::string>&);
  private:
    std::unordered_map<std::string,
        std::string(Command::*)(const std::vector<std::string>&)> com_coll;
  };

} // myDB

#endif // COMMAND_H