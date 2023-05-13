#include "../include/ta_objects/esc_reference.hpp"

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

std::string TAReference::getClass()
{
    return "TAReference";
}