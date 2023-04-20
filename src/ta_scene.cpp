#include "../include/parser.hpp"

TAObject& TAScene::Parse(std::string& sceneName, OptionalMap m)
{
    if (!m.has_value())
    {
        return *this;
    }

    auto propertyHeaders = m.value();
    
    name = sceneName;

    HandleGrabLines<TAString>(
        propertyHeaders,
        { "description", "desc" },
        [&](std::string item) { HandleAppend(desc, item); }
    );

    HandleGrabLines<TAReference>(
        propertyHeaders,
        { "items" },
        [&](std::string item) { HandleAppend(items, TAReference().Parse(item)); }
    );

    auto exitsTemp = std::vector<std::string>();

    HandleGrabLines<std::string>(
        propertyHeaders,
        { "exits" },
        [&](std::string item) { HandleAppend(exitsTemp, item); },
        false
    );

    auto exitHeaders = Parser::GetHeaders(exitsTemp, true, 3);

    for (auto exitHeader : exitHeaders)
    {
        exits.push_back(std::pair(exitHeader.first, TAReference().Parse(exitHeader.second[0])));
    }

    std::cout <<std::endl;
    std::cout << name.str << desc.str << std::endl;
    for (auto item : items)
        std::cout << item.valid << item.str << std::endl;
    for (auto exit : exits)
        std::cout << std::get<1>(exit).valid << std::get<0>(exit).str << std::get<1>(exit).str << std::endl;
    std::cout << std::endl;

    valid = true;
    return *this;
}