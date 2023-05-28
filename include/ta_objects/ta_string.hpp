#pragma once

#include <iostream>

#include "ta_object.hpp"

namespace tap {
class TAString : public TAObject
{
public:
    TAString();
    TAString(std::string str);
public:
    std::string str;

    TAObject& Parse(std::string& str, OptionalMap m = std::nullopt) override;

    TAObject* Create() override;

    std::string& getString() override;

    int getType() override;
};
}