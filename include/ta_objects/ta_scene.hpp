#pragma once

#include <iostream>
#include <string>
#include <algorithm>

#include "../ta_object.hpp"
#include "esc_reference.hpp"

#include "string_extensions.hpp"

class TAScene : public TAObject
{
public:
    ~TAScene();
public:
    TAObject* name;
    TAObject* desc;
    std::vector<TAObject*> items;
    std::vector<std::tuple<TAString, TAObject*>> exits;

    TAObject& Parse(std::string&, OptionalMap = std::nullopt) override; 

    TAObject* Create() override;

    std::string& getString() override;
};