#include "../../include/ta_objects/ta_state.hpp"

TAState::TAState(size_t* currentState) : currentState(currentState)
{
}

TAState::~TAState()
{
    delete currentState;
    for (auto state : states)
    {
        delete state;
    }
    states.clear();
}

TAObject& TAState::Parse(std::string&, OptionalMap m)
{
    if (!m.has_value())
        return *this;
    
    for (auto state : m.value())
    {
        if (ltrim(state.first)[0] != '%')
        {
            TAObject* newObj;
            if (HasDeliminator(state.second.second[0].second, '$'))
                newObj = new TAReference();
            else
                newObj = new TAString();

            auto combinedString = CombineString(state.second.second);
            states.push_back(&newObj->Parse(combinedString));
        }
        else
        {
            std::vector<TAObject *> objects;
            for (auto stateItem : state.second.second)
            {
                TAObject* newObj;

                if (HasDeliminator(stateItem.second, '$'))
                    newObj = new TAReference();
                else
                    newObj = new TAString();

                objects.push_back(&newObj->Parse(stateItem.second));
            }
            states.push_back(&(new TAArray(objects))->Parse(defaultName, std::nullopt));
        }
    }

    if (states.size() > 0)
        valid = true;
    return *this;
}

TAObject* TAState::Create()
{
    return new TAState(NULL);
}

std::string& TAState::getString()
{
    return states.size() > 0 && currentState != NULL
        ? states[*currentState]->getString()
        : defaultName;
}

std::string TAState::getClass()
{
    return "TAState";
}
