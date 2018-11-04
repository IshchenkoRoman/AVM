#include "lexer.hpp"

Lexer::Lexer() {

}

Lexer::~Lexer() {

}

Lexer&      Lexer::operator=(const Lexer& cls) {

    if (&cls == this)
        return (*this);

    return (*this);
}

std::pair<std::string, std::string> Lexer::createToken(std::string &s) {

    std::smatch slice;
    // std::regex currentRe = *(_regularExpressions[0]);
    std::regex currentRe ("(\\w*){1}.?(\\w*)");
    std::regex_search(s, slice, currentRe);
    std::string typeToken = static_cast<std::string>(slice[2]);

    // currentRe = *(_regularExpressions[1]);
    std::regex currentRe1 ("(\\(([^<>*\\d]*\\d[^<>]*)\\))");
    std::regex_search(s, slice, currentRe1);

    std::string valueToken = static_cast<std::string>(slice[2]);

    std::pair<std::string, std::string> res (typeToken, valueToken);

    return (res);
}
