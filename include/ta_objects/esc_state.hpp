#pragma once

#include "../ta_object.hpp"

#include <memory>

#include "ta_string.hpp"
#include "esc_reference.hpp"
#include "ta_array.hpp"

class TAState : public TAObject
{
public:
    TAState(size_t* currentState) : currentState(currentState)
    {
    }

    ~TAState()
    {
        delete currentState;
        for (auto state : states)
        {
            delete state;
        }
        states.clear();
    }
public:
    std::vector<TAObject *> states;
    size_t* currentState;

    TAObject& Parse(std::string&, OptionalMap m = std::nullopt) override
    {
        if (!m.has_value())
            return *this;
        
        for (auto state : m.value())
        {
            if (ltrim(state.first)[0] != '%')
            {
                TAObject* newObj;
                if (HasDeliminator(state.second[0], '$'))
                    newObj = new TAReference();
                else
                    newObj = new TAString();

                auto combinedString = CombineString(state.second);
                states.push_back(&newObj->Parse(combinedString));
            }
            else
            {
                std::vector<TAObject *> objects;
                for (auto stateItem : state.second)
                {
                    TAObject* newObj;

                    if (HasDeliminator(stateItem, '$'))
                        newObj = new TAReference();
                    else
                        newObj = new TAString();

                    objects.push_back(&newObj->Parse(stateItem));
                }
                states.push_back(&(new TAArray(objects))->Parse(defaultName, std::nullopt));
            }
        }

        if (states.size() > 0)
            valid = true;
        return *this;
    }

    TAObject* Create() override
    {
        return new TAState(NULL);
    }

    std::string& getString() override
    {
        return states.size() > 0 && currentState != NULL
            ? states[*currentState]->getString()
            : defaultName;
    }

    std::string getClass() override
    {
        return "TAState";
    }
};