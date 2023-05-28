#include "../../include/ta_objects/ta_string.hpp"

using namespace tap;

TAString::TAString()
{
}

TAString::TAString(std::string str) : str(str)
{
    valid = true;
}

TAObject& TAString::Parse(std::string& str, OptionalMap m)
{
    this->str = str;

    valid = true;
    return *this;
}

TAObject* TAString::Create()
{
    return new TAString;
}

std::string& TAString::getString()
{
    return str;
}

int TAString::getType()
{
    return 8;
}
