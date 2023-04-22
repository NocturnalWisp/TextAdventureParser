#pragma once

#include "../ta_object.hpp"

class TAString : public TAObject
{
public:
    TAString(){}
    TAString(std::string str) : str(str) { valid = true; }
public:
    std::string str;

    TAObject& Parse(std::string& str, OptionalMap m = std::nullopt) override
    {
        this->str = str;

        valid = true;
        return *this;
    }

    std::string& getString() override
    {
        return str;
    }
};