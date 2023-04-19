#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "include/parser.hpp"
#include "include/string_extensions.hpp"

int main(int , char *[])
{
    Parser* parser = new Parser();

    std::ifstream stream("assets/game.ta");
    std::stringstream buffer;
    buffer << stream.rdbuf();
    std::string gameString = buffer.str();

    TextAdventure TextAdventure = parser->Parse(gameString);

    return 0;
}