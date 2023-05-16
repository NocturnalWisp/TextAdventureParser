#pragma once

#include "../ta_object.hpp"

#include <memory>

#include "ta_string.hpp"
#include "ta_reference.hpp"
#include "ta_array.hpp"

class TAState : public TAObject
{
public:
    TAState(size_t* currentState);

    ~TAState();
public:
    std::vector<TAObject *> states;
    size_t* currentState;

    TAObject& Parse(std::string&, OptionalMap m = std::nullopt) override;

    TAObject* Create() override;

    std::string& getString() override;

    std::string getClass() override;
};