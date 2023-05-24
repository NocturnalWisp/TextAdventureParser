#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <memory>

#include "include/parser.hpp"
#include "include/string_extensions.hpp"

#include "include/ta_exceptions/ta_parse_exception.hpp"

int main(int , char *[])
{
    std::unique_ptr<Parser> parser = std::unique_ptr<Parser>(new Parser());

    std::ifstream stream("game.ta");
    std::stringstream buffer;
    buffer << stream.rdbuf();
    std::string gameString = buffer.str();

    try
    {
        TextAdventure TextAdventure = parser->Parse(gameString);
    }
    catch(const tap::ParseException& e)
    {
        std::cerr << e.what() << std::endl;
    }
    

    return 0;
}