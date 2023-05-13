#include "../include/parser.hpp"

TAItem::~TAItem()
{
    delete name;
    delete desc;

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
    return name->getString();
}

std::string TAItem::getClass()
{
    return "TAItem";
}

TAObject& TAItem::Parse(std::string& itemName, OptionalMap m)
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

void TAItem::getDescription(OptionalMap m)
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

void TAItem::getActions(OptionalMap m)
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
            auto functionHeaders = Parser::GetHeaders(
                actionHeader.second,
                true,
                4
            );


            TAAction* action = new TAAction();
            action->statement = new TAString(actionHeader.first);
            action->functionName = new TAString(std::get<0>(SpliceString(actionHeader.second[0], ':', true)));

            for (int i = 1; i < actionHeader.second.size(); i++)
            {
                auto arg = ltrim(actionHeader.second[i]);
                if (arg[0] == '$')
                {
                    action->arguments.push_back(&(new TAReference())->Parse(arg));
                }
                else
                {
                    action->arguments.push_back(&(new TAString())->Parse(arg));
                }
            }

            actions.push_back(action);
        }
    }
}