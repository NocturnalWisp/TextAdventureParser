#pragma once

#include <iostream>
#include <string>
#include <algorithm>

#include "../ta_object.hpp"
#include "esc_reference.hpp"
#include "esc_state.hpp"

#include "../string_extensions.hpp"

class TAScene : public TAObject
{
public:
    ~TAScene();
public:
    TAObject* name;
    TAObject* desc = new TAString();
    std::vector<TAObject*> items;
    std::vector<std::tuple<TAString, TAObject*>> exits;

    size_t currentState = 0;

    TAObject& Parse(std::string&, OptionalMap = std::nullopt) override; 

    TAObject* Create() override;

    std::string& getString() override;
private:
    void getDescription(OptionalMap m);
    void getItems(OptionalMap m);
    void getExits(OptionalMap m);
};