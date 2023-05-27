#include "../../include/ta_objects/ta_action.hpp"

TAAction::~TAAction()
{
    delete statement;
    delete functionName;
    for (auto arg : arguments)
        delete arg;
    arguments.clear();
}
TAObject& TAAction::Parse(std::string& str, OptionalMap m)
{
    return *this;
}

TAObject& TAAction::Parse(std::pair<std::string, std::pair<size_t, std::vector<std::string>>> action)
{
    statement = new TAString(action.first);

    auto function = action.second.second[0];

    functionName = new TAString(std::get<0>(SpliceString(RemoveDeliminators(function), ':', true)));

    for (int i = 1; i < action.second.second.size(); i++)
    {
        auto arg = RemoveDeliminators(ltrim(action.second.second[i]));

        if (arg[0] == '$')
        {
            arguments.push_back(&(new TAReference())->Parse(arg));
        }
        else
        {
            arguments.push_back(&(new TAString())->Parse(arg));
        }
    }

    valid = true;
    return *this;
}

TAObject* TAAction::Create()
{
    return new TAAction;
}

std::string& TAAction::getString()
{
    str = statement->getString() + " : " +
        functionName->getString() + "(";
    for (auto arg : arguments)
    {
        str.append(arg->getString() + ", ");
    }
    str.append("\b\b)");
    return str;
}

std::string TAAction::getClass()
{
    return "TAAction";
}