#include "parser.h"

void myDB::Parser::parse_code(const std::string& m_str)
{
  std::string bar;
  tokens.clear();

  for(int i = 0; i <= m_str.size(); ++i) 
  {
    if (m_str[i] == '\0' || m_str[i] == ' ') {
      if (bar.size() != 0) {
        tokens.push_back(bar);
        bar.clear();
      }
    } else if (m_str[i] == '/' || m_str[i] == '=' || m_str[i] == '-') {
      if(!bar.empty())
        tokens.push_back(bar);
      bar.clear();
      bar.push_back(m_str[i]);
      if(!bar.empty())
        tokens.push_back(bar);
      bar.clear();
    } else {
      bar.push_back(m_str[i]);
    }
  }
}

std::vector<std::string> myDB::Parser::get_tokens() const
{
  return tokens;
}