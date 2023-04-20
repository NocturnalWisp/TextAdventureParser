#include "../include/ta_objects/esc_reference.hpp"

TAReference& TAReference::Parse (std::string& str, OptionalMap m)
{
    if (!HasDeliminator(str, '$'))
        return *this;

    this->str = RemoveDeliminators(str);

    valid = true;
    return *this;
}