#include "../ta_object.hpp"

#include "string_extensions.hpp"

class TAReference : public TAObject
{
public:
    TAReference(){}
    TAReference(std::string str) : str(str) {}
    TAReference& Parse (std::string& str, OptionalMap m = std::nullopt) override;
public:
    std::string str;
};