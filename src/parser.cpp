#include <iostream>
#include <string>
#include <vector>

#include "../include/string_extensions.hpp"
#include "../include/parser.hpp"

Parser::Parser()
{

}

TextAdventure Parser::Parse(std::string& file)
{
    TextAdventure textAdventure = TextAdventure();

    std::vector lines = GetLines(file);

    auto headers = GetHeaders(lines, true);

    for (auto header : headers)
    {
        for (auto strategy : parseStrategies)
        {
            if (header.first.compare(strategy.first) == 0)
            {
                //TODO: Attach result to text adventure object.
                std::vector<TAObject> result = strategy.second->Parse(header.second);
            }
        }
    }

    return textAdventure;
}