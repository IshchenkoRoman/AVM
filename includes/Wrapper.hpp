#ifndef WRAPPER_HPP
# define WRAPPER_HPP

#include <sys/stat.h>
#include <unistd.h>
#include <fstream>

#include <utility>
#include <string>

#include "lexer.hpp"
#include "parcer.hpp"
#include "IOperand.hpp"
#include "VM.hpp"

typedef int(VM::*classFunction)(void);

class Wrapper {


  public:
    Wrapper();
    Wrapper(Wrapper const &cls);
    ~Wrapper();

    void    core(int argc, char **argv);
    int     listen(std::string &s, std::map<std::string, classFunction> *mapFunction, VM &vm, Parcer &_parcer);
    int     execute(int i, std::string command, std::map<std::string, classFunction> *mapFunction, VM &vm);

    int     existFile(const std::string &filename);
    int     validName(const std::string &filename);
    int     readFile(const std::string &filename, std::map<std::string, classFunction> *mapFunction, VM &vm, Parcer &_parcer);

    bool    ends_with(std::string const & value, std::string const & ending);
    int     getStatusExit(void) {
        return (_statusExit);
    }

    void    setStatusExit(int i) {

        _statusExit = i;
    };

    void reset(void) {
        _statusExit = 1;
    }
  private:
    Lexer _lexer;
    Parcer _parcer;

    int    _statusExit;

    Wrapper& operator=(const Wrapper&);

};

#endif
