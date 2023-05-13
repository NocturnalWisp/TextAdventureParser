#pragma once

#include <iostream>
#include <string>

#include "../ta_object.hpp"

class TAEvent : public TAObject
{
private:
    ~TAEvent()
    {
        delete name;
    }
public:
    TAObject* name;

    TAObject& Parse(std::string& str, OptionalMap m) override
    {
        // for (auto s : items)
            // std::cout << s << std::endl;

        return *this;
    }

    TAObject* Create() override
    {
        return new TAEvent;
    };

    std::string& getString() override
    {
        return name->getString();
    }

    std::string getClass() override
    {
        return "TAEvent";
    }
};