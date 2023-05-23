#include "../../include/ta_objects/ta_event.hpp"

#include "../../include/parser.hpp"

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

std::string TAEvent::getClass()
{
    return "TAEvent";
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

    std::cout << std::endl;
    std::cout << name->getString() << std::endl;
    if (desc != nullptr)
        std::cout << desc->getString() << std::endl;
    for (auto action : actions)
        std::cout << action->getString() << std::endl;
    std::cout << std::endl;

    valid = true;
    return *this;
};

void TAEvent::getDescription(OptionalMap m)
{
    HandleGrabLines<std::string>(
        m.value(),
        { "description", "desc" },
        {},
        [&](auto item, auto delim)
            {
                desc->getString().append(item);
            },
            true
    );
}

void TAEvent::getActions(OptionalMap m)
{
    std::vector<std::string> actionLines;
    HandleGrabLines<std::string>(
        m.value(),
        { "action", "actions" },
        {},
        [&](auto item, auto delim)
            {
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