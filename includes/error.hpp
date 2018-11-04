#ifndef ERROR_H
# define ERROR_H

#include <exception>
#include <sstream>
#include <string>

class InterfaceError : public std::exception {

  using std::exception::what;
  virtual void  msg() = 0;
  virtual char  const   *what() throw() = 0;
};

class ZeroDivisionError : public InterfaceError {

public:
  ZeroDivisionError() {
  };
  void msg() {

      std::stringstream ss;
      ss << "\033[1;31mZeroDivisionError: division by zero.\033[0m";

      _msg = ss.str();
  }

  char const * what() throw() {

    this->msg();

    return (_msg.c_str());
  }

protected:
  std::string _msg;
};

class OverflowError : public InterfaceError {

public:
  void msg() {

      std::stringstream ss;
      ss << "\033[1;31mValue overflowed!\033[0m";

      _msg = ss.str();
  }

  char const * what() throw() {

    this->msg();

    return (_msg.c_str());
  }

protected:
  std::string _msg;
};

class UnderlowError : public InterfaceError {

public:
  void msg() {

      std::stringstream ss;
      ss << "\033[1;31mValue underflowed!\033[0m";

      _msg = ss.str();
  }

  char const * what() throw() {

    this->msg();

    return (_msg.c_str());
  }

protected:
  std::string _msg;
};

class EmptyStackError : public InterfaceError {

public:
  void msg() {

      std::stringstream ss;
      ss << "\033[1;31mAction on empty stack!\033[0m";

      _msg = ss.str();
  }

  char const * what() throw() {

    this->msg();

    return (_msg.c_str());
  }

protected:
  std::string _msg;
};

class LTWError : public InterfaceError {

public:
  void msg() {

      std::stringstream ss;
      ss << "\033[1;31mThe stack is composed of strictly less that two values when an arithmetic instruction is executed.\033[0m";

      _msg = ss.str();
  }

  char const * what() throw() {

    this->msg();

    return (_msg.c_str());
  }

protected:
  std::string _msg;
};

class UnknowInstructionError : public InterfaceError {

public:
  void msg() {

      std::stringstream ss;
      ss << "\033[1;31mAn instruction is unknown.\033[0m";

      _msg = ss.str();
  }

  char const * what() throw() {

    this->msg();

    return (_msg.c_str());
  }

protected:
  std::string _msg;
};

class ExitDoesntExistError : public InterfaceError {

public:
  void msg() {

      std::stringstream ss;
      ss << "\033[1;31mThe program doesn’t have an exit instruction.\033[0m";

      _msg = ss.str();
  }

  char const * what() throw() {

    this->msg();

    return (_msg.c_str());
  }

protected:
  std::string _msg;
};

class AssertError : public InterfaceError {

public:
  void msg() {

      std::stringstream ss;
      ss << "\033[1;31mAn assert instruction is not true.\033[0m";

      _msg = ss.str();
  }

  char const * what() throw() {

    this->msg();

    return (_msg.c_str());
  }

protected:
  std::string _msg;
};

class FileNotExist : public InterfaceError {

public:
  void msg() {

      std::stringstream ss;
      ss << "\033[1;31mFile doesn't exist!\033[0m";

      _msg = ss.str();
  }

  char const * what() throw() {

    this->msg();

    return (_msg.c_str());
  }

protected:
  std::string _msg;
};

class FileNotReadable : public InterfaceError {

public:
  void msg() {

      std::stringstream ss;
      ss << "\033[1;31mFile cann't be readed!\033[0m";

      _msg = ss.str();
  }

  char const * what() throw() {

    this->msg();

    return (_msg.c_str());
  }

protected:
  std::string _msg;
};

class ExitCommandUsed : public InterfaceError {

public:
  void msg() {

      std::stringstream ss;
      ss << "\033[1;31mCommand exit was used, you can only finish execution (write \";;\")\033[0m";

      _msg = ss.str();
  }

  char const * what() throw() {

    this->msg();

    return (_msg.c_str());
  }

protected:
  std::string _msg;
};

#endif
