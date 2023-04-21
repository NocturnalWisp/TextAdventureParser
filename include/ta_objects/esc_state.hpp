#pragma once

#include "../ta_object.hpp"

#include <memory>

#include "ta_string.hpp"

class TAState : public TAObject
{
public:
    std::vector<TAObject> states;
    size_t currentState = 0;

    TAObject& Parse(std::string&, OptionalMap = std::nullopt) override
    {
        

        return *this;
    }

    std::string& getString() override
    {
        return states[currentState].getString();
    }
};