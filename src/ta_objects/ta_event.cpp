#include "../../include/ta_objects/ta_event.hpp"

#include "../../include/parser.hpp"

using namespace tap;

TAEvent::~TAEvent()
{
    delete name;
    delete desc;

    for (auto action : actions)
        delete action;
    actions.clear();
}

TAObject* TAEvent::Create()
{
    return new TAEvent;
};

std::string& TAEvent::getString()
{
    return name->getString();
}

int TAEvent::getType()
{
    return 3;
}

TAObject& TAEvent::Parse(std::string& itemName, OptionalMap m)
{
    if (!m.has_value())
    {
        return *this;
    }

    auto propertyHeaders = m.value();
    
    name = new TAString(itemName);

    getDescription(m);
    getActions(m);

    valid = true;
    return *this;
};

void TAEvent::getDescription(OptionalMap m)
{
    HandleGrabLines(
        m.value(),
        { "description", "desc" },
        {},
        [&](auto item, auto delim)
            {
                desc->getString().append(item.second);
            },
            true
#ifdef DEBUGTAP
        , [&]()
            {
                throw tap::ParseException("Could not get a description from event \"" + this->name->getString() + "\".",
                    Parser::startHeaderLine,
                    4);
            }
#endif
    );
}

void TAEvent::getActions(OptionalMap m)
{
    size_t actionLinesNumber;
    LineList actionLines;
    HandleGrabLines(
        m.value(),
        { "action", "actions" },
        {},
        [&](auto item, auto headerInfo)
            {
                actionLinesNumber = headerInfo.first;
                actionLines.push_back(item);
            },
            false
#ifdef DEBUGTAP
        , [&]()
            {
                throw tap::ParseException("Could not get any actions in event \"" + this->name->getString() + "\".",
                    Parser::startHeaderLine,
                    4);
            }
#endif
    );

    if (actionLines.size() > 0)
    {
        Parser::startHeaderLine = actionLinesNumber;
        auto actionHeaders = Parser::GetHeaders(
            actionLines,
            true,
            3
        );

        for (auto actionHeader : actionHeaders)
        {
            TAAction* action = new TAAction();

            action->Parse(actionHeader);

            actions.push_back(action);
        }
    }
}