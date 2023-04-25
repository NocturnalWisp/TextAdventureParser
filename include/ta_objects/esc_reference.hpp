#pragma once

#include "../ta_object.hpp"

#include "../string_extensions.hpp"

class TAReference : public TAObject
{
public:
    TAReference(){}
    TAReference(std::string str) : str(str) {}
    TAObject& Parse (std::string& str, OptionalMap m = std::nullopt) override;
public:
    std::string str;

    std::string& getString() override;
};