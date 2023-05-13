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
    std::vector<TAReference*> items;
    std::vector<std::tuple<TAString, TAReference*>> exits;

    size_t currentState = 0;

    TAObject& Parse(std::string&, OptionalMap = std::nullopt) override; 

    TAObject* Create() override;

    std::string& getString() override;
    std::string getClass() override { return "TAScene"; }
private:
    void getDescription(OptionalMap m);
    void getItems(OptionalMap m);
    void getExits(OptionalMap m);
};