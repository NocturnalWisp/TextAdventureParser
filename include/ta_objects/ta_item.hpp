#pragma once

#include <iostream>
#include <string>

#include "../ta_object.hpp"
#include "ta_action.hpp"

class TAItem : public TAObject
{
public:
    ~TAItem();
public:
    TAObject* name;
    TAObject* desc = new TAString();
    std::vector<TAAction*> actions;

    TAObject& Parse(std::string& str, OptionalMap m) override;

    TAObject* Create() override;

    std::string& getString() override;
    std::string getClass() override;
private:
    void getDescription(OptionalMap m);
    void getActions(OptionalMap m);
};