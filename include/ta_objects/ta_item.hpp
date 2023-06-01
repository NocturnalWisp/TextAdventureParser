#pragma once

#include <iostream>
#include <string>

#include "ta_object.hpp"
#include "ta_action.hpp"

namespace tap {
class TAItem : public TAObject
{
public:
    ~TAItem();
public:
    TAString name = TAString();
    TAString desc = TAString();
    std::vector<TAAction*> actions;

    TAObject& Parse(std::string& str, OptionalMap m) override;

    TAObject* Create() override;

    std::string& getString() override;
    int getType() override;
private:
    void getDescription(OptionalMap m);
    void getActions(OptionalMap m);
};
}