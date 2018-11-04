#ifndef LEXER_HPP
# define LEXER_HPP

#include <iostream>
#include <regex>
#include <utility>

class Lexer {

  public:
    Lexer();
    ~Lexer();
    Lexer& operator=(const Lexer&);

    std::string                          cleanCommand(std::string &s);
    std::pair <std::string, std::string> createToken(std::string &s);

  private:

    Lexer(const Lexer &);
};

#endif
