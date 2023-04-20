#pragma once

#include <iostream>
#include <string>

#include "../ta_object.hpp"

class TAItem : public TAObject
{
public:
    TAObject& Parse(std::string& str, OptionalMap m) override
    {
        // for (auto s : items)
            // std::cout << s << std::endl;

        return *this;
    }
};