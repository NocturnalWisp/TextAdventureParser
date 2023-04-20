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
    TAString name;
    TAString desc;
    std::vector<TAReference> items;
    std::vector<std::tuple<TAString, TAReference>> exits;

    TAObject& Parse(std::string&, OptionalMap = std::nullopt) override; 

    TAObject* Create() override
    {
        return new TAScene;
    };
};