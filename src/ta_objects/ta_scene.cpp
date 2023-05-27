#include "../../include/ta_objects/ta_scene.hpp"

#include "../../include/parser.hpp"

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
        std::cout << item->getString() << std::endl;
    for (auto exit : exits)
        std::cout << std::get<0>(exit).str << " : " << std::get<1>(exit)->getString() << std::endl;
    std::cout << std::endl;

    valid = true;
    return *this;
};

void TAScene::getDescription(OptionalMap m)
{
    size_t stateLinesNumber;
    std::vector<std::string> stateLines;
    HandleGrabLines<std::string>(
        m.value(),
        { "description", "desc" },
        { '%' },
        [&](auto item, auto delim)
            {
                if (delim != '%')
                {
                    desc->getString().append(ltrim(item.second));
                }
                else
                {
                    stateLinesNumber = item.first;
                    stateLines.push_back(item.second);
                }
            },
            false
    );

    if (stateLines.size() > 0)
    {
        // Use state to represent the data.
        Parser::startHeaderLine = stateLinesNumber;
        auto stateHeaders = Parser::GetHeaders(
            stateLines,
            false,
            3
        );

        delete desc;
        TAState* state = new TAState(&currentState);
        state->Parse(defaultName, stateHeaders);
        desc = state;
    }
}

void TAScene::getItems(OptionalMap m)
{
    size_t stateLinesNumber;
    std::vector<std::string> stateLines;
    HandleGrabLines<TAReference>(
        m.value(),
        { "items" },
        { '%' },
        [&](auto item, auto delim)
        {
            if (delim != '%')
                items.push_back((TAReference*)&(new TAReference())->Parse(item.second));
            else
            {
                stateLinesNumber = item.first;
                stateLines.push_back(item.second);
            }
        },
        false
    );

    if (stateLines.size() > 0)
    {
        Parser::startHeaderLine = stateLinesNumber;
        auto stateHeaders = Parser::GetHeaders(
            stateLines,
            false,
            3
        );

        items.push_back((TAState*)&(new TAState(&currentState))->Parse(defaultName, stateHeaders));
    }
}

void TAScene::getExits(OptionalMap m)
{
    size_t exitLinesNumber;
    std::vector<std::string> exitLines;
    HandleGrabLines<TAReference>(
        m.value(),
        { "exits" },
        { '%' },
        [&](auto item, auto delim)
            {
                exitLinesNumber = item.first;
                exitLines.push_back(item.second);
            },
        false
    );

    if (exitLines.size() > 0)
    {
        Parser::startHeaderLine = exitLinesNumber;
        auto exitHeaders = Parser::GetHeaders(
            exitLines,
            true,
            3
        );

        for (auto exitHeader : exitHeaders)
        {
            auto exitReference = ltrim(exitHeader.second.second[0]);
            auto exit = (TAReference*)&(new TAReference())->Parse(exitReference);
            exits.push_back(std::pair(exitHeader.first, exit));
        }
    }
}