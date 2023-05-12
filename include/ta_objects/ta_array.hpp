#pragma once

#include <iostream>
#include <string>

#include "../ta_object.hpp"
#include "../string_extensions.hpp"

class TAArray : public TAObject
{
public:
    TAArray(std::vector<TAObject *> objects) : objects(objects)
    {

    }
public:
    std::vector<TAObject *> objects;

    TAObject& Parse(std::string& str, OptionalMap m) override
    {
        valid = true;
        return *this;
    }


    std::string& getString() override
    {
        str = "%";
        for (auto object : objects)
        {
            str.append(object->getString() + "&");
        }
        return str;
    }
private:
    std::string str;
};