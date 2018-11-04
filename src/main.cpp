#include <iostream>
#include <regex>
#include <array>

#include <iostream>
#include <string>


#include "parcer.hpp"
#include "lexer.hpp"
#include "Wrapper.hpp"

#include "IOperand.hpp"

int     main(int argc, char **argv) {

    Wrapper wrapper = Wrapper();
    wrapper.core(argc, argv);

    return (0);
}
