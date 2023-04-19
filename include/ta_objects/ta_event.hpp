#pragma once

#include <iostream>
#include <string>

#include "../ta_object.hpp"

class TAEvent : public TAObject
{
public:
    std::vector<TAObject> Parse(std::vector<std::string> items) override
    {
        // for (auto s : items)
            // std::cout << s << std::endl;

        return std::vector<TAObject>();
    }
};