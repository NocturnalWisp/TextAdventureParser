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

TAObject* TAScene::Create()
{
    return new TAScene;
};

std::string& TAScene::getString()
{
    return name->getString();
}

TAObject& TAScene::Parse(std::string& sceneName, OptionalMap m)
{
    if (!m.has_value())
    {
        return *this;
    }

    auto propertyHeaders = m.value();
    
    name = new TAString(sceneName);

    getDescription(m);
    getItems(m);
    getExits(m);

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
};

void TAScene::getDescription(OptionalMap m)
{
    std::vector<std::string> stateLines;
    HandleGrabLines<std::string>(
        m.value(),
        { "description", "desc" },
        { '%' },
        [&](auto item, auto delim)
            {
                if (delim != '%')
                {
                    desc->getString().append(ltrim(item));
                }
                else
                {
                    stateLines.push_back(item);
                }
            },
            false
    );

    if (stateLines.size() > 0)
    {
        // Use state to represent the data.
        auto stateHeaders = Parser::GetHeaders(
            stateLines,
            false,
            3
        );

        delete desc;
        TAState* state = new TAState(currentState);
        state->Parse(defaultName, stateHeaders);
        desc = state;
    }
}

void TAScene::getItems(OptionalMap m)
{
    std::vector<std::string> stateLines;
    HandleGrabLines<TAReference>(
        m.value(),
        { "items" },
        { '%' },
        [&](auto item, auto delim)
        {
            if (delim != '%')
                items.push_back(&(new TAReference())->Parse(item));
            else
                stateLines.push_back(item);
        },
        false
    );

    if (stateLines.size() > 0)
    {
        auto stateHeaders = Parser::GetHeaders(
            stateLines,
            false,
            3
        );

        items.push_back(&(new TAState(currentState))->Parse(defaultName, stateHeaders));
    }
}

void TAScene::getExits(OptionalMap m)
{
    HandleGrabLines<TAReference>(
        m.value(),
        { "exits" },
        { '%' },
        [&](auto item, auto delim)
            {
                auto exit = &(new TAReference())->Parse(item);
                exits.push_back(std::pair(TAString(), exit));
            },
        false
    );
}