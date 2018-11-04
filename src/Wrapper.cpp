#include "Wrapper.hpp"

#include <functional>

typedef std::function<int(void)>  func;
typedef int (VM::*magic)(void);

Wrapper::Wrapper() {

    this->_lexer = Lexer();
    this->_parcer = Parcer();

    this->_statusExit = 1;
}

Wrapper::~Wrapper() {

}

Wrapper::Wrapper(Wrapper const &cls) {

    this->_lexer = cls._lexer;
    this->_parcer = cls._parcer;
}

bool Wrapper::ends_with(std::string const & value, std::string const & ending)
{
    if (ending.size() > value.size()) return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

int     Wrapper::existFile(const std::string &filename) {

    struct  stat buffer;
    return (stat (filename.c_str(), &buffer) == 0);
}

int     Wrapper::validName(const std::string &filename) {

    return (filename.find(".avm") != std::string::npos);
}

int     Wrapper::readFile(const std::string &filename, std::map<std::string, classFunction> *mapFunction, VM &vm, Parcer &_parcer) {

    int             i;
    std::string     line;
    std::ifstream   myfile(filename);

    try {
    if (myfile.is_open() && ends_with(filename, ".avm")) {

            while (getline(myfile, line) && getStatusExit()) {

                i = _parcer.parseString(line);
                try {
                  if (i == -1){
                    throw UnknowInstructionError();
                  }
                }
                catch (UnknowInstructionError &err) {
      
                  std::cout << err.what() << std::endl;
                }
                if (i >= 0) {
                  execute(i, line, mapFunction, vm);
                }
                if (i == 5) {
                    setStatusExit(0);
                    return (0);
                }
            }
            myfile.close();
            return (1);
        }
        else if (access(filename.c_str(), R_OK) == -1) {
            throw FileNotReadable();
        }
        else {
            throw FileNotExist();
        }
    }
    catch (FileNotExist &err) {

        std::cout << err.what() << std::endl;
        return (0);
    }
    catch (FileNotReadable &err) {

        std::cout << err.what() << std::endl;
        return (0);
    }
}

int   Wrapper::execute(int i, std::string command, std::map<std::string, classFunction> *mapFunction, VM &vm) {

    int flag_42;

    flag_42 = 0;

    try {

        if (i == 1) {
              if (getStatusExit()) {

                magic m = (*mapFunction)[command];
                flag_42 = (vm.*m)();
              }
            else if (!getStatusExit() && (command.find(";;") != std::string::npos)) {
                magic m = (*mapFunction)[command];
                flag_42 = (vm.*m)();
            }
            else {
                throw ExitCommandUsed();
            }
        }
        else if ((i == 2 || i == 3) && (getStatusExit())) {

            std::pair <std::string, std::string> l = _lexer.createToken(command);
            std::string com = _parcer.matchString(command);
            const IOperand *operand = vm.createOperand(l.first, l.second);
            if (command.find("push") != std::string::npos)
                vm.push(operand);
            else
                vm.assert(operand);
        }
        else if (i != 4 && i != 5) {
            throw ExitCommandUsed();
        }
    }

  catch (EmptyStackError &err) {

    std::cout << err.what() << std::endl;

    return (0);
  }
  catch (LTWError &err) {

    std::cout << err.what() << std::endl;

    return (0);
  }
  catch (OverflowError &err) {

    std::cout << err.what() << std::endl;

    return (0);
  }
  catch (UnderlowError &err) {

    std::cout << err.what() << std::endl;

    return (0);
  }
  catch (AssertError &err) {

    std::cout << err.what() << std::endl;

    return (0);
  }
  catch (ZeroDivisionError &err) {

      std::cout << err.what() << std::endl;

      return (0);
  }

  catch (ExitCommandUsed &err) {

      std::cout << err.what() << std::endl;

      return (1);
  }

  if (flag_42 == 42) {

    return (flag_42);
  }

  return (1);
}

int  Wrapper::listen(std::string &s, std::map<std::string, classFunction> *mapFunction, VM &vm, Parcer &_parcer) {

    int i;
    int status;

    i = _parcer.parseString(s);
    if (i > 0) {
        status = execute(i, s, mapFunction, vm);
        if (!status || status == 42) {
            return (status);
        }
    }
    else {

      try {
        if (i == -1)
          throw UnknowInstructionError();
      }
      catch (UnknowInstructionError &err) {
        std::cout << err.what() << std::endl;
        return (0);
      }
  }
  return (i);
}

void  Wrapper::core(int argc, char **argv) {

    int         i;
    std::string s;

    VM& vm = VM::getInstance();

  // https://stackoverflow.com/questions/10901959/function-pointers-in-c-error-must-use-or-to-call-pointer-to-memb
  // https://stackoverflow.com/questions/44678806/c-calling-function-when-using-map-of-function-pointer
  // http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2013/n3690.pdf 5.5

  std::map<std::string, classFunction> *mapFunction = vm.createMapFunction();

  if (argc == 1) {
      std::getline(std::cin, s);
      while ((i = listen(s, mapFunction, vm, _parcer))) {

          if (i == 5) {

              //It's 'exit'
              setStatusExit(0);
          }

          if (i == -1) {

              // It's ';;'
              break;
          }
          if (i == 42) {

            break;
          }
          std::getline(std::cin, s);
          std::cin.clear();
      }

      try {
          if (getStatusExit()) {

              throw ExitDoesntExistError();
          }
      }
      catch (ExitDoesntExistError &err) {

          std::cout << err.what() << std::endl;
      }
  }
  else {

    std::string arg;
    for (i = 1; i < argc; ++i) {
        arg = static_cast<std::string>(argv[i]);
        std::cout << "\033[1;36m******************************************\033[0m\n" << std::endl;
        std::cout << "\033[0;35mExecute file: [\033[0;33m" + arg + "\033[0;35m]\033[0m\n" << std::endl;
        readFile(arg, mapFunction, vm, _parcer);

        try {
            if (getStatusExit()) {

                throw ExitDoesntExistError();
            }
        }
        catch (ExitDoesntExistError &err) {

            std::cout << err.what() << std::endl;
        }

        std::cout << "\033[1;36m##########################################\033[0m\n\n" << std::endl;
        vm.reset();
        reset();
    }
  }

  delete mapFunction;
}
