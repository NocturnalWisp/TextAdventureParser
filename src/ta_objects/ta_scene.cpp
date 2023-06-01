#include "../../include/ta_objects/ta_scene.hpp"

#include "../../include/parser.hpp"

using namespace tap;

TAScene::~TAScene()
{
    delete name;
    delete desc;

    for (auto item : items)
        delete item;
    items.clear();

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

int TAScene::getType()
{
    return 6;
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

    valid = true;
    return *this;
};

void TAScene::getDescription(OptionalMap m)
{
    size_t stateLinesNumber;
    LineList stateLines;
    HandleGrabLines(
        m.value(),
        { "description", "desc" },
        { '%' },
        [&](auto item, auto headerInfo)
            {
                if (headerInfo.second != '%')
                {
                    desc->getString().append(ltrim(item.second));
                }
                else
                {
                    stateLinesNumber = headerInfo.first;
                    stateLines.push_back(item);
                }
            },
        false
#ifdef DEBUGTAP
        , [&]()
            {
                throw tap::ParseException("Could not get a description from scene \"" + this->name->getString() + "\".",
                    Parser::startHeaderLine,
                    4);
            }
#endif
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
    LineList stateLines;
    HandleGrabLines(
        m.value(),
        { "items" },
        { '%' },
        [&](auto item, auto headerInfo)
        {
            if (headerInfo.second != '%')
                items.push_back((TAReference*)&(new TAReference())->Parse(item.second));
            else
            {
                stateLinesNumber = headerInfo.first;
                stateLines.push_back(item);
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
    LineList exitLines;
    HandleGrabLines(
        m.value(),
        { "exits" },
        { '%' },
        [&](auto item, auto headerInfo)
            {
                exitLinesNumber = headerInfo.first;
                exitLines.push_back(item);
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
            auto exitReference = ltrim(exitHeader.second.second[0].second);

            auto exit = TAReference();
            exit.Parse(exitReference);

            exits.push_back(std::pair(exitHeader.first, exit));
        }
    }
}