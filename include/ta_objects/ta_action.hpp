#pragma once

#include <iostream>
#include <string>

#include "../ta_object.hpp"
#include "../string_extensions.hpp"
#include "ta_reference.hpp"
#include "ta_string.hpp"

class TAAction : public TAObject
{
public:
    ~TAAction();
private:
    std::string str;
public:
    TAObject* statement;
    TAObject* functionName;
    std::vector<TAObject *> arguments;

    TAObject& Parse(std::string& str, OptionalMap m);

    TAObject& Parse(std::pair<std::string, std::vector<std::string>> action);

    TAObject* Create() override;

    std::string& getString() override;

    std::string getClass() override;
};