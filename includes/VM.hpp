#ifndef VM_HPP
# define VM_HPP

#include <stdlib.h>

#include <vector>
#include <string>
#include <iostream>
#include <map>

#include "IOperand.hpp"

typedef std::function<int(void)> f;
// typedef std::map< std::string, std::function<int(VM::*)(void)> > mapFunc;

class VM {

public:
  typedef int(VM::*classFunction)(void);

  static VM& getInstance() {

    static  VM vm;

    return (vm);
  }

  size_t                  getSizeStrip() {

    return (_strip.size());
  };

  std::map<std::string, classFunction> *createMapFunction(void) {

    std::map<std::string, classFunction> *mapFunc = new std::map<std::string, classFunction>;
    mapFunc->insert(std::make_pair("add", &VM::add));
    mapFunc->insert(std::make_pair("sub", &VM::sub));
    mapFunc->insert(std::make_pair("mul", &VM::mul));
    mapFunc->insert(std::make_pair("div", &VM::div));
    mapFunc->insert(std::make_pair("mod", &VM::mod));
    mapFunc->insert(std::make_pair("print", &VM::print));
    mapFunc->insert(std::make_pair("exit", &VM::exit));
    mapFunc->insert(std::make_pair("dump", &VM::dump));
    mapFunc->insert(std::make_pair("pop", &VM::pop));
    mapFunc->insert(std::make_pair("help", &VM::help));


    return(mapFunc);
  }

  void reset( void ) {
      _strip.clear();
  }

  const IOperand* createOperand(std::string type, std::string value) {

      int eType = eOperandTypeConverter.at(type);

      return (IOperand::createOperand(static_cast<eOperandType>(eType), value));

  };

  int pop( void ){

    size_t sizeStrip = getSizeStrip();

    if (sizeStrip) {
      const IOperand* val = _strip.back();
      _strip.pop_back();

      delete val;
    }
    else
    {
      throw EmptyStackError();
      return (0);
    }
    return (1);
  }

  int       add( void ) {

    size_t sizeStrip = getSizeStrip();

    if (sizeStrip >= 2) {

      const IOperand* val1 = _strip.back();
      _strip.pop_back();
      const IOperand* val2 = _strip.back();
      _strip.pop_back();

      const IOperand* res = *val1 + *val2;

      delete val1;
      delete val2;

      push(res);
      return (1);
    }
    else {
      throw LTWError();
      return (0);
    }
  };

  int       sub( void ){

    size_t sizeStrip = getSizeStrip();

    if (sizeStrip >= 2) {

      const IOperand* val1 = _strip.back();
      _strip.pop_back();
      const IOperand* val2 = _strip.back();
      _strip.pop_back();

      const IOperand* res = *val2 - *val1;

      delete val1;
      delete val2;

      push(res);
      return (1);
    }
    else {
      throw LTWError();
      return (0);
    }
  }

  int       mul( void ){

    size_t sizeStrip = getSizeStrip();

    if (sizeStrip >= 2) {

      const IOperand* val1 = _strip.back();
      _strip.pop_back();
      const IOperand* val2 = _strip.back();
      _strip.pop_back();

      const IOperand* res = *val2 * *val1;

      delete val1;
      delete val2;

      push(res);
      return (1);
    }
    else {
      throw LTWError();
      return (0);
    }
  }

  int       mod( void ){

    size_t sizeStrip = getSizeStrip();

    if (sizeStrip >= 2) {

      const IOperand* val1 = _strip.back();
      _strip.pop_back();
      const IOperand* val2 = _strip.back();
      _strip.pop_back();

      try {

          const IOperand* res = *val2 % *val1;

          delete val1;
          delete val2;

          push(res);
          return (1);
      }
      catch (ZeroDivisionError &err) {
        std::cout << err.what() << std::endl;

        delete val1;
        delete val2;

        return (42);
      }
    }
    else {
      throw LTWError();
      return (0);
    }
    return (1);
  }

  int       div( void ){

    size_t sizeStrip = getSizeStrip();

    if (sizeStrip >= 2) {

      const IOperand* val1 = _strip.back();
      _strip.pop_back();
      const IOperand* val2 = _strip.back();
      _strip.pop_back();

      try {
        const IOperand* res = *val2 / *val1;
        push(res);

        delete val1;
        delete val2;

        return (1);
      }
      catch (ZeroDivisionError &err) {
        std::cout << err.what() << std::endl;

        delete val1;
        delete val2;


        return (42);
      }


    }
    else {
      throw LTWError();
      return (0);
    }
  }

  int       print( void ){

    const IOperand* val;
    const IOperand* int8;

    size_t sizeStrip = getSizeStrip();

    if (sizeStrip) {

      val = _strip.back();
      int8 = IOperand::createOperand(Int8, val->toString());
      assert(int8);
      delete int8;
    }
    else {
      throw EmptyStackError();
      return (0);
    }

    std::cout << static_cast<char>(stoi(val->toString())) << std::endl;
    return(1);
  }

  int       exit( void ){

    return (0);
  }

  int       assert( const IOperand* operand ) {

    int   status = 0;

    std::vector<const IOperand *> currStrip = getStrip();

    if (getSizeStrip()) {
        const IOperand *lastOp = currStrip.back();
        status = *lastOp == *operand;
    }
    else {
        throw EmptyStackError();
    }
    if (!status) {
        throw AssertError();
    }

    return (status);
  }

  int       push( const IOperand* operand ){

      _strip.push_back(operand);
      return (1);
  };

  std::vector<const IOperand *> getStrip() {

    return _strip;
  }

  int       dump( void ){

    size_t sizeStrip = getSizeStrip();

    if (sizeStrip) {

      std::vector<const IOperand *> currStrip = getStrip();
      std::reverse(currStrip.begin(), currStrip.end());
      size_t                              i = 1;

      std::cout << "\033[1;32m==========================================\033[0m" << std::endl;

      for (auto &m : currStrip) {

        std::string s = m->toString();

        std::cout << "\033[1;36m#[" << i << "]\033[0m " << m->toString() << std::endl;
        ++i;
      }

      std::cout << "\033[1;32m==========================================\033[0m" << std::endl;
    }
    else {
      std::string msg = "\033[1;31mStack is empty!\033[0m";
      std::cout << msg << std::endl;
    }
    return (1);
  };

    int     help(void) {

        std::cout << "\033[1;32m******************************************\033[0m" << std::endl;
        std::cout << "\033[1;32m  To create operand type IOperand and put on stack write command:"
        "push int8[16|32]|float|double(arg), where 'arg' is excepted value for IOperand.\n"
        "Keep in mind 'Overflow' and 'Underflow' for each of values.\n"
        "For asserting command instead 'push' write 'assert', if asserting failed- then program "
        "terminated.\n\n"
        "  With values on Stack you can done below command:\n\t@add\n\t@sub\n\t@mul\n\t@div\n\t@mod\n"
        "  None commutative operands such as '-','/','%' in relevant commans 'sub','div','mod' "
        "works as example:\nIn the stack v1 on v2 on 'stack_tail', the calculation in infix notation v2 op v1.\n"
        "  Be shure that vaules on stack >= than 2, or you'll get error.\n"
        "  To print all values call @dump.\n"
        "  Command @print work as assert for int8.\n"
        "  End for executing consider command 'exit' AND ';;' in command line and simple 'exit' in .avm file.\n"
        "  Example how to use:\n\t'push int8(32);your comment'\n"
        "\tassert double(23);  ----- > error\n"
        "******************************************\033[0m" << std::endl;

        return (1);
    }

    std::vector< std::pair<std::string, int(VM::*)(void)> > initArrayOfFunctions ( void ) {

    std::vector< std::pair<std::string, int(VM::*)(void)> > arrayOfFunction;

    arrayOfFunction.reserve(7);

    arrayOfFunction.push_back({"add", &VM::add});
    arrayOfFunction.push_back({"sub", &VM::sub});
    arrayOfFunction.push_back({"mul", &VM::mul});
    arrayOfFunction.push_back({"mod", &VM::mod});
    arrayOfFunction.push_back({"div", &VM::div});
    arrayOfFunction.push_back({"print", &VM::print});
    arrayOfFunction.push_back({"exit", &VM::exit});
    arrayOfFunction.push_back({"dump", &VM::exit});

    return (arrayOfFunction);
  }

private:
  std::vector<const IOperand *> _strip;
  VM() {};
  VM& operator=(const VM& );
  VM(VM &);
  ~VM() {

      for (size_t i = 0; i < _strip.size(); ++i) {

          delete _strip[i];
      }
  };
  void                    setSizeStrip(size_t);

};

#endif
