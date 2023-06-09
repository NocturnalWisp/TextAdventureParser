#include "../../include/ta_objects/ta_item.hpp"

#include "../../include/parser.hpp"

using namespace tap;

TAItem::~TAItem()
{
    for (auto action : actions)
        delete action;
    actions.clear();
}

TAObject* TAItem::Create()
{
    return new TAItem;
};

std::string& TAItem::getString()
{
    return name.getString();
}

int TAItem::getType()
{
    return 4;
}

TAObject& TAItem::Parse(std::string& itemName, OptionalMap m)
{
    if (!m.has_value())
    {
        return *this;
    }

    auto propertyHeaders = m.value();
    
    name.str = itemName;

    getDescription(m);
    getActions(m);

    valid = true;
    return *this;
};

void TAItem::getDescription(OptionalMap m)
{
    HandleGrabLines(
        m.value(),
        { "description", "desc" },
        {},
        [&](auto item, auto delim)
            {
                desc.str.append(item.second);
            },
        true
#ifdef DEBUGTAP
        , [&]()
            {
                throw tap::ParseException("Could not get a description from item \"" + name.getString() + "\".",
                    Parser::startHeaderLine,
                    4);
            }
#endif
    );
}

void TAItem::getActions(OptionalMap m)
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
    );

    if (actionLines.size() > 0)
    {
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