#ifndef IOPERAND_HPP
# define IOPERAND_HPP


#include <string>
#include <map>

#include <limits>

#include <iostream>
#include "error.hpp"

#include <iostream>     // std::cout, std::fixed
#include <iomanip>      // std::setprecision
#include <iomanip> // setprecision
#include <sstream> // stringstream
#include <cmath>

#include "fenv.h" // double (over|under)flow

enum eOperandType { Int8, Int16, Int32, Float, Double };
static std::map<std::string, int> eOperandTypeConverter = { {"int8", Int8},
                      {"int16", Int16}, {"int32", Int32}, {"float", Float}, {"double", Double} };

class IOperand {

  public:

    virtual int             getPrecision( void ) const = 0; // Precision of the type of the instance
    virtual eOperandType    getType( void ) const = 0;      // Type of instance

    static IOperand const * createOperand( eOperandType type, std::string const & value );

    virtual IOperand const * operator+( IOperand const & rhs ) const = 0; // Sum
    virtual IOperand const * operator-( IOperand const & rhs ) const = 0; // Difference
    virtual IOperand const * operator*( IOperand const & rhs ) const = 0; // Product
    virtual IOperand const * operator/( IOperand const & rhs ) const = 0; // Quotient
    virtual IOperand const * operator%( IOperand const & rhs ) const = 0; // Modulo
    virtual bool             operator==(IOperand const & rhs) const = 0;
    virtual std::string const & toString( void ) const = 0; // String representation of the instance
    virtual ~IOperand( void ) {};

  private:
    static IOperand const * createInt8(std::string const & value);
    static IOperand const * createInt16(std::string const & value);
    static IOperand const * createInt32(std::string const & value);
    static IOperand const * createFloat(std::string const & value);
    static IOperand const * createDouble(std::string const & value);
};

template <typename Type>
class Operand : public IOperand {

public:
    Operand();
    Operand(Type val, eOperandType type);
    Operand(Operand const &);
    virtual ~Operand();

    IOperand const *	operator+(IOperand const & rhs) const;
    IOperand const *	operator-(IOperand const & rhs) const;
    IOperand const *	operator*(IOperand const & rhs) const;
	IOperand const *	operator/(IOperand const & rhs) const;
	IOperand const *	operator%(IOperand const & rhs) const;
	bool				operator==(IOperand const & rhs) const;

	Type				getValue() const;
    eOperandType        getType(void) const;
    std::string const &	toString(void) const;
    bool                isNumeric(std::string const &s);

private:
    eOperandType        highestPrecision(IOperand const &rhs) const;
    Type                value;
    std::string         string_value;
    eOperandType        type;

    int                 getPrecision( void ) const {
        return (-42);
    };
};

template <typename T>
std::string const &	Operand<T>::toString() const
{
	return this->string_value;
}

template <typename Type>
Operand<Type>::Operand() {

    this->value = 0;
    this->string_value = "0";
    this->type = Int32;
}

template <typename Type>
Operand<Type>::Operand(Type value, eOperandType type) {

    this->value = value;
    this->string_value = std::to_string(value);
    this->type = type;
}

template <typename Type>
eOperandType Operand<Type>::highestPrecision(IOperand const &rhs) const {

  eOperandType typeRhs = rhs.getType();

  return this->type > typeRhs ? this->type : typeRhs;
}

template <typename Type>
Type Operand<Type>::getValue() const {

  return value;
}

template <typename Type>
eOperandType Operand<Type>::getType() const {

  return type;
}

template <typename Type>
IOperand const *	Operand<Type>::operator+(IOperand const & rhs) const {

  eOperandType ht = highestPrecision(rhs);
  double rvalue = std::stod(rhs.toString());

  return (IOperand::createOperand(ht, std::to_string(this->value + rvalue)));
}

template <typename Type>
IOperand const *	Operand<Type>::operator-(IOperand const & rhs) const {

  eOperandType ht = highestPrecision(rhs);
  double rvalue = std::stod(rhs.toString());

  return (IOperand::createOperand(ht, std::to_string(this->value - rvalue)));
}

template <typename Type>
IOperand const *	Operand<Type>::operator*(IOperand const & rhs) const {

  eOperandType ht = highestPrecision(rhs);
  double rvalue = std::stod(rhs.toString());

  return (IOperand::createOperand(ht, std::to_string(this->value * rvalue)));
}

template <typename Type>
IOperand const *	Operand<Type>::operator/(IOperand const & rhs) const {

  eOperandType ht = highestPrecision(rhs);
  double rvalue = std::stod(rhs.toString());
  if (rvalue == 0)
    throw ZeroDivisionError();

  return (IOperand::createOperand(ht, std::to_string(this->value / rvalue)));
}

template <typename Type>
IOperand const *	Operand<Type>::operator%(IOperand const & rhs) const {

  eOperandType ht = highestPrecision(rhs);
  ht = (ht == Double || ht == Float) ?  Int32 : ht;
  int rvalue = std::stoi(rhs.toString());
  int lvalue = static_cast<int>(this->value);
  if (rvalue == 0)
    throw ZeroDivisionError();

  return (IOperand::createOperand(ht, std::to_string(lvalue % rvalue)));
}

template <typename Type>
bool             Operand<Type>::operator==(IOperand const &rhs) const {

  return (this->type == rhs.getType() && this->string_value == rhs.toString());
}

template <typename T>
Operand<T>::~Operand() {

}

#endif
