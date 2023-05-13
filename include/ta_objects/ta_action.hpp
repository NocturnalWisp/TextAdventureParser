#pragma once

#include <iostream>
#include <string>

#include "../ta_object.hpp"
#include "../string_extensions.hpp"

class TAAction : public TAObject
{
public:
    ~TAAction()
    {
        delete statement;
        delete functionName;
        for (auto arg : arguments)
            delete arg;
        arguments.clear();
    }
private:
    std::string str;
public:
    TAObject* statement;
    TAObject* functionName;
    std::vector<TAObject *> arguments;

    TAObject& Parse(std::string& str, OptionalMap m) override
    {
        valid = true;
        return *this;
    }

    TAObject* Create() override
    {
        return new TAAction;
    }

    std::string& getString() override
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

    std::string getClass() override
    {
        return "TAAction";
    }
};