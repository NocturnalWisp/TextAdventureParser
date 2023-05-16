#pragma once

#include <iostream>
#include <string>

#include "../ta_object.hpp"
#include "../string_extensions.hpp"

class TAArray : public TAObject
{
public:
    TAArray(std::vector<TAObject *> objects);
public:
    std::vector<TAObject *> objects;

    TAObject& Parse(std::string& str, OptionalMap m) override;

    TAObject* Create() override;

    std::string& getString() override;

    std::string getClass() override;
private:
    std::string str;
};