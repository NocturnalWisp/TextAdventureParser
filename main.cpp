#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <memory>

#include "include/parser.hpp"
#include "include/string_extensions.hpp"

int main(int , char *[])
{
    std::unique_ptr<Parser> parser = std::unique_ptr<Parser>(new Parser());

    std::ifstream stream("game.ta");
    std::stringstream buffer;
    buffer << stream.rdbuf();
    std::string gameString = buffer.str();

    TextAdventure TextAdventure = parser->Parse(gameString);

    return 0;
}