#include "IOperand.hpp"

template<typename Operandtype, typename Targettype>
bool isOverFlow(Operandtype val, Targettype dummy) {

    dummy = dummy;
    if (val > std::numeric_limits<Targettype>::max()) {
        throw OverflowError();
    }
    else if (val < std::numeric_limits<Targettype>::lowest()) {
        throw UnderlowError();
    }
    return (val > std::numeric_limits<Targettype>::max() || val < std::numeric_limits<Targettype>::lowest());
}

IOperand const * IOperand::createOperand ( eOperandType type, std::string const &val ) {

  IOperand const * createdOperand = NULL;

  switch(type) {
    case Int8:
      createdOperand = IOperand::createInt8(val);
      break;
    case Int16:
      createdOperand = IOperand::createInt16(val);
      break;
    case Int32:
      createdOperand = IOperand::createInt32(val);
      break;
    case Float:
      createdOperand = IOperand::createFloat(val);
      break;
    case Double:
      createdOperand = IOperand::createDouble(val);
      break;
    default :
      break;
  }

  return (createdOperand);
}

IOperand const * IOperand::createInt8(std::string const &value ) {

    double val = std::stod(value);
    int8_t dummy = -42;
    if (isOverFlow<double, int8_t>(val, dummy))
      throw OverflowError();

    return (new Operand<int8_t>(static_cast<short int>(val), Int8));
}

IOperand const * IOperand::createInt16(std::string const &value ) {

    double val = std::stod(value);
    int16_t dummy = -42;
    if (isOverFlow<double, int16_t>(val, dummy))
      throw OverflowError();

    return (new Operand<int16_t>(static_cast<int>(val), Int16));
}

IOperand const * IOperand::createInt32(std::string const &value ) {

    double val = std::stod(value);
    int32_t dummy = -42;
    if (isOverFlow<double, int32_t>(val, dummy))
      throw OverflowError();

    return (new Operand<int32_t>(static_cast<long int>(val), Int32));
}

IOperand const * IOperand::createFloat(std::string const &value ) {

    double val = std::stod(value);
    float dummy = -42;
    if (isOverFlow<double, float>(val, dummy))
      throw OverflowError();
    return (new Operand<float>(val, Float));
}

IOperand const * IOperand::createDouble(std::string const &value ) {

    std::string const dummy = "-";
    auto result = double();
    std::istringstream i (value);

    i >> result;
    i >> std::ws;

    if (!(!i.fail() && i.eof())) {

        if (value.find("-") != std::string::npos)
            throw UnderlowError();
        else
            throw OverflowError();
        return NULL;
    }
    else {
        double  val = std::stod(value);
        return (new Operand<float>(val, Double));
    }
}
