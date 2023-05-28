#include "../../include/ta_objects/ta_reference.hpp"

using namespace tap;

TAObject& TAReference::Parse (std::string& str, OptionalMap m)
{
    if (!HasDeliminator(str, '$'))
        return *this;

    this->str = ltrim(RemoveDeliminators(str));

    valid = true;
    return *this;
}

TAObject* TAReference::Create()
{
    return new TAReference;
}

std::string& TAReference::getString()
{
    return str;
};

int TAReference::getType()
{
    return 5;
}