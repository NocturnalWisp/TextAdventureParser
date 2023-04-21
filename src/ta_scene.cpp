#include "../include/parser.hpp"

TAScene::~TAScene()
{
    delete name;
    delete desc;

    for (auto item : items)
        delete item;
    items.clear();

    for (auto exit : exits)
        delete std::get<1>(exit);
    exits.clear();
}

TAObject& TAScene::Parse(std::string& sceneName, OptionalMap m)
{
    if (!m.has_value())
    {
        return *this;
    }

    auto propertyHeaders = m.value();
    
    name = new TAString(sceneName);

    HandleGrabLines<TAString>(
        propertyHeaders,
        { "description", "desc" },
        { '%' },
        [&](auto item, auto delim)
            {
                std::cout << item << std::endl;
                if (delim != '%')
                    desc = &(new TAString())->Parse(item);
                else
                    desc = &(new TAState())->Parse(item);
            }
    );

    HandleGrabLines<TAReference>(
        propertyHeaders,
        { "items" },
        { '%' },
        [&](auto item, auto delim) { items.push_back(&(new TAReference())->Parse(item)); }
    );

    HandleGrabLines<TAReference>(
        propertyHeaders,
        { "exits" },
        { '%' },
        [&](auto item, auto delim)
            {
                auto exit = &(new TAReference())->Parse(item);
                exits.push_back(std::pair(TAString(), exit));
            },
        false
    );

    std::cout << std::endl;
    std::cout << name->getString() << std::endl;
    if (desc != nullptr)
        std::cout << desc->getString() << std::endl;
    for (auto item : items)
        std::cout << item->valid << item->getString() << std::endl;
    for (auto exit : exits)
        std::cout << std::get<1>(exit)->valid << std::get<0>(exit).str << std::get<1>(exit)->getString() << std::endl;
    std::cout << std::endl;

    valid = true;
    return *this;
}

TAObject* TAScene::Create()
{
    return new TAScene;
};

std::string& TAScene::getString()
{
    return name->getString();
};