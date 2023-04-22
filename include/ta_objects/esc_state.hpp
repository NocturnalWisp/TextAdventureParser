#pragma once

#include "../ta_object.hpp"

#include <memory>

#include "ta_string.hpp"
#include "esc_reference.hpp"

class TAState : public TAObject
{
public:
    TAState(size_t& currentState) : currentState(currentState)
    {
    }
public:
    std::vector<TAObject> states;
    size_t& currentState;

    TAObject& Parse(std::string&, OptionalMap m = std::nullopt) override
    {
        if (!m.has_value())
            return *this;
        
        for (auto state : m.value())
        {
            if (HasDeliminator(state.second[0], '$'))
            {
                auto combinedString = CombineString(state.second);
                states.push_back(TAReference().Parse(combinedString));
            }
            else
            {
                auto combinedString = CombineString(state.second);
                states.push_back(TAString().Parse(combinedString));
            }
        }

        if (states.size() > 0)
            valid = true;
        return *this;
    }

    std::string& getString() override
    {
        return states.size() > 0
            ? states[currentState].getString()
            : defaultName;
    }
};