#pragma once

#include <iostream>
#include <string>

#include "ta_object.hpp"
#include "ta_action.hpp"
#include "ta_string.hpp"

namespace tap {
class TAEvent : public TAObject
{
public:
    ~TAEvent();
public:
    TAObject* name;
    TAObject* desc = new TAString();
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