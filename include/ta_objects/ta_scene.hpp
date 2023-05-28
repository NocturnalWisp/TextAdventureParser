#pragma once

#include <iostream>
#include <string>
#include <algorithm>

#include "ta_object.hpp"
#include "ta_reference.hpp"
#include "ta_state.hpp"
#include "ta_string.hpp"

#include "../string_extensions.hpp"

namespace tap {
class TAScene : public TAObject
{
public:
    ~TAScene();
public:
    TAObject* name;
    TAObject* desc = new TAString();
    std::vector<TAObject*> items;
    std::vector<std::tuple<TAString, TAReference*>> exits;

    size_t currentState = 0;

    TAObject& Parse(std::string&, OptionalMap = std::nullopt) override; 

    TAObject* Create() override;

    std::string& getString() override;
    int getType() override;
private:
    void getDescription(OptionalMap m);
    void getItems(OptionalMap m);
    void getExits(OptionalMap m);
};
}