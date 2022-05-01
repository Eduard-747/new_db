#ifndef PARSER_H
#define PARSER_H

#include <iostream>

#include <vector>
#include <string>

namespace myDB
{
  
  class Parser
  {
  public:
    void parse_code(const std::string&);
    std::vector<std::string> get_tokens() const;
  private:
    std::vector<std::string> tokens;
  };

} // myDB

#endif // PARSER_H