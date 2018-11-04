#include "parcer.hpp"

//#############
//TODO: DELETE
#include <iostream>
//############

Parcer&      Parcer::operator=(const Parcer& cls) {

    if (&cls == this)
        return (*this);

    this->_regularExpressions = cls._regularExpressions;
    this->_sizeRegularExpressions = cls._sizeRegularExpressions;
    return (*this);
}

Parcer::Parcer(void) {

  /*
    Regular Expression that catch valid commands
  */
    this->_regularExpressions.reserve(6);

    std::regex *reSingle = new std::regex ("(^(pop)|(dump)|(add)|(sub)|(mul)|(div)|(mod)|(print)|(help))(((\\s*;[^;](.*))|(;))\n?)?$");
    std::regex *reComment = new std::regex ("(^((;[^;](.*))|(;))\n?)?$");
    std::regex *rePushAssertInt = new std::regex ("^((push )|(assert ))(((int)((8)|(16)|(32))(\\(\\-?((0)|([1-9]\\d*))\\))))(((\\s*;[^;](.*))|(;))\n?)?$");
    std::regex *rePushAsserFloat = new std::regex ("^((push )|(assert ))(((float)|(double))(\\(\\-?((0)|((0\\.\\d*)|([1-9]\\d*\\.?\\d*)))\\)))(((;[^;](.*))|(;))\n?)?$");
    std::regex *reExit = new std::regex ("(^(exit)(((;[^;](.*))|(;))\n?)?$)");
    std::regex *reEnd = new std::regex ("(^(;;)$)");

    this->_regularExpressions[0] = reEnd;
    this->_regularExpressions[1] = reSingle;
    this->_regularExpressions[2] = rePushAssertInt;
    this->_regularExpressions[3] = rePushAsserFloat;
    this->_regularExpressions[4] = reComment;
    this->_regularExpressions[5] = reExit;

    this->_sizeRegularExpressions = 6;

}

Parcer::Parcer(const Parcer &cls) {

  this->_regularExpressions = cls._regularExpressions;
  this->_sizeRegularExpressions = cls._sizeRegularExpressions;
}

Parcer::~Parcer() {

  size_t sizeRegularExpressions = getSizeRegularExpressions();

  for (size_t i = 0; i < sizeRegularExpressions; i++) {

    delete this->_regularExpressions[i];
  }
}

size_t              Parcer::getSizeRegularExpressions(void) {

    return (_sizeRegularExpressions);
}

std::vector<std::regex *> Parcer::getRegularExpressions(void) {

    return (_regularExpressions);
}

std::string         Parcer::matchString(std::string &s) {

    std::smatch match;
    std::regex currentRe = std::regex("^((push)|(assert))");
    if (std::regex_search(s, match, currentRe)) {
      return (match.str());
    }
    return nullptr;
}

int                 Parcer::parseString(std::string &s) {

    size_t                    sizeRegularExpressions = this->getSizeRegularExpressions();

    for (size_t i = 0; i < sizeRegularExpressions; i++) {

        // That's bad, but i donn't know how get it with getter and don't catch SegFault
        std::regex currentRe = *(_regularExpressions[i]);
        if (std::regex_match(s.begin(), s.end(), currentRe)) {
          return (i);
        }
    }

    return (-1);
}
