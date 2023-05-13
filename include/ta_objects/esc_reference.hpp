#pragma once

#include "../ta_object.hpp"

#include "../string_extensions.hpp"

class TAReference : public TAObject
{
public:
    TAReference(){}
    TAReference(std::string str) : str(str) {}
public:
    std::string str;

    TAObject& Parse (std::string& str, OptionalMap m = std::nullopt) override;
    TAObject* Create() override;

    std::string& getString() override;
    std::string getClass() override;
};