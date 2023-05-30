#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <memory>

#include "include/parser.hpp"
#include "include/string_extensions.hpp"

#include "include/ta_exceptions/ta_parse_exception.hpp"

using namespace tap;

int main(int , char *[])
{
    std::unique_ptr<Parser> parser = std::unique_ptr<Parser>(new Parser());

    try
    {
        TextAdventure textAdventure = parser->Parse("game.ta");

        std::cout << textAdventure.getString() << std::endl;
    }
    catch(const tap::ParseException& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}