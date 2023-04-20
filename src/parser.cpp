#include <iostream>
#include <string>
#include <vector>

#include "../include/string_extensions.hpp"
#include "../include/parser.hpp"

Parser::Parser() {}

TextAdventure Parser::Parse(std::string& file)
{
    TextAdventure textAdventure = TextAdventure();

    std::vector lines = GetLines(file);

    // (Scenes, Items, Events, etc...)
    auto headers = GetHeaders(lines, true);

    for (auto header : headers)
    {
        for (auto strategy : parseStrategies)
        {
            if (header.first.compare(strategy.first) == 0)
            {
                // (Individual objects)
                auto taObjHeader = GetHeaders(header.second, true, 1);

                for (auto headerForObject : taObjHeader)
                {
                    // (Object internal properties.)
                    auto objectHeader = GetHeaders(headerForObject.second, true, 2);
                    //TODO: Attach result to text adventure object.
                    auto objectName = std::string(headerForObject.first);
                    TAObject& result = strategy.second->Parse(objectName, objectHeader);

                    auto newStrat = strategy.second->Create();
                    delete strategy.second;
                    strategy.second = newStrat;
                }
            }
        }
    }

    return textAdventure;
}

// Returns a map of indented items.
std::map<std::string, std::vector<std::string>> Parser::GetHeaders(std::vector<std::string>& lines, bool applyColonRemoval, int indentCount)
{
    auto headers = std::map<std::string, std::vector<std::string>>();

    std::vector<std::string> internalLines = std::vector<std::string>();
    bool inLineHeader = false;
    std::string lineHeader;
    for (std::string line : lines)
    {
        if (line[0] == '#' || line[0] == 0)
            continue;

        if (line[indentCount*4] == ' ' && inLineHeader)
        {
            internalLines.push_back(line);
            continue;
        }

        if (inLineHeader)
        {
            headers.insert(std::pair(lineHeader, internalLines));
            internalLines.clear();
        }

        lineHeader = applyColonRemoval ? std::get<0>(SpliceString(line, ':', true)) : line;
        inLineHeader = true;
    }

    // Insert the last header.
    if (!lineHeader.empty())
        headers.insert(std::pair(lineHeader, internalLines));

    return headers;
}