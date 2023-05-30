#include "../include/parser.hpp"

using namespace tap;

Parser::Parser()
{
}

size_t Parser::startHeaderLine = 0;

TextAdventure Parser::Parse(std::string path)
{
    std::ifstream stream(path);
    std::stringstream buffer;
    buffer << stream.rdbuf();

    auto file = buffer.str();

    TextAdventure textAdventure = TextAdventure();

    auto lines = GetLines(file);

    // Throw error: empty file.
#ifdef DEBUGTAP
    if (lines.size() == 0)
        throw tap::ParseException("Empty file, nothing to parse.", 0, 0);
#endif

    // (Scenes, Items, Events, etc...)
    startHeaderLine = 0;
    auto headers = GetHeaders(lines, true);

    for (auto header : headers)
    {
        bool foundHeader = false;
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

                    auto objectName = std::string(headerForObject.first);
                    TAObject* result = strategy.second->Create();
                    result->Parse(objectName, objectHeader);

                    textAdventure.ParseStrategy(result);

                    auto newStrat = strategy.second->Create();
                    delete strategy.second;
                    strategy.second = newStrat;
                }
                foundHeader = true;
                break;
            }
        }
        
        // Throw error: invalid main header.
#ifdef DEBUGTAP
        if (!foundHeader)
        {
            std::string errorMsg = "Failed to interpret header \"" + RemoveDeliminators(header.first) + "\". Main headers allowed: ";
            for (auto strat : parseStrategies)
            {
                errorMsg.append(strat.first + ", ");
            }
            errorMsg = errorMsg.substr(0, errorMsg.size()-2);
            errorMsg.append(".");
            throw tap::ParseException(errorMsg, header.second.first, 0);
        }
#endif
    }

    //TODO: throw error if no strategies were complete. (Empty file)
    // if (lines.size() == 0)
    //     throw tap::ParseException("Empty file, nothing to parse.", 0, 0);

    return textAdventure;
}

// Returns a map of indented items.
HeaderMap Parser::GetHeaders(LineList& lines, bool applyColonRemoval, int indentCount)
{
    auto headers = HeaderMap();

    std::vector<std::pair<size_t, std::string>> internalLines = std::vector<std::pair<size_t, std::string>>();
    bool inLineHeader = false;
    std::string lineHeader;

    size_t headerLineNumber;
    for (auto line : lines)
    {
        if (inLineHeader && line.second[indentCount*4] == ' ')
        {
            internalLines.push_back(line);
            continue;
        }

        if (ltrim(line.second)[0] == '#' || RemoveDeliminators(line.second).size() == 0)
            continue;

        if (inLineHeader)
        {
            headers.insert(std::pair(lineHeader, std::pair(headerLineNumber, internalLines)));
            internalLines.clear();
        }

        lineHeader = applyColonRemoval ? std::get<0>(SpliceString(line.second, ':', true)) : line.second;
        inLineHeader = true;

        headerLineNumber = line.first+1;
    }

    // Insert the last header.
    if (!lineHeader.empty())
        headers.insert(std::pair(lineHeader, std::pair(headerLineNumber, internalLines)));

    return headers;
}