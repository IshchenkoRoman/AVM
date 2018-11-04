#ifndef PARCER_HPP
# define PARCER_HPP

#include <string>
#include <vector>
#include <regex>

class Parcer {

    private:
      std::vector<std::regex *>   _regularExpressions;
      size_t                      _sizeRegularExpressions;

    public:
        Parcer(void);
        Parcer(const Parcer &cls);
        Parcer& operator=(const Parcer&);
        ~Parcer();

        size_t                    getSizeRegularExpressions(void);
        std::vector<std::regex *> getRegularExpressions(void);
        std::string               matchString(std::string &s);


        int                       parseString(std::string &s);
};

#endif
