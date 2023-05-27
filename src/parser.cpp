#include "../include/parser.hpp"

Parser::Parser() {}

size_t Parser::startHeaderLine = 0;

TextAdventure Parser::Parse(std::string& file)
{
    TextAdventure textAdventure = TextAdventure();

    std::vector lines = GetLines(file);

    if (lines.size() == 0)
        throw tap::ParseException("Empty file, nothing to parse.", 0, 0);

    // (Scenes, Items, Events, etc...)
    startHeaderLine = 0;
    auto headers = GetHeaders(lines, true);

    for (auto header : headers)
    {
        for (auto strategy : parseStrategies)
        {
            if (header.first.compare(strategy.first) == 0)
            {
                // (Individual objects)
                startHeaderLine = header.second.first;
                auto taObjHeader = GetHeaders(header.second.second, true, 1);

                for (auto headerForObject : taObjHeader)
                {
                    // (Object internal properties.)
                    startHeaderLine = headerForObject.second.first;
                    auto objectHeader = GetHeaders(headerForObject.second.second, true, 2);
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
HeaderMap Parser::GetHeaders(std::vector<std::string>& lines, bool applyColonRemoval, int indentCount)
{
    auto headers = HeaderMap();

    std::vector<std::string> internalLines = std::vector<std::string>();
    bool inLineHeader = false;
    std::string lineHeader;

    size_t lineNumber = startHeaderLine-1;
    size_t headerLineNumber;
    for (std::string line : lines)
    {
        lineNumber++;

        if (line[0] == '#' || line[0] == 0)
            continue;

        if (line[indentCount*4] == ' ' && inLineHeader)
        {
            internalLines.push_back(line);
            continue;
        }

        if (inLineHeader)
        {
            headers.insert(std::pair(lineHeader, std::pair(headerLineNumber, internalLines)));
            internalLines.clear();
        }

        lineHeader = applyColonRemoval ? std::get<0>(SpliceString(line, ':', true)) : line;
        inLineHeader = true;

        headerLineNumber = lineNumber;
    }

    // Insert the last header.
    if (!lineHeader.empty())
        headers.insert(std::pair(lineHeader, std::pair(headerLineNumber, internalLines)));

    return headers;
}