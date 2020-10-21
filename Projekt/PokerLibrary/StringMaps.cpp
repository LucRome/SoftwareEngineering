#include "pch.h"
#include "StringMaps.h"

std::string MyClass::suit_string(suits s)
{
    return suitMap.find(s)->second;
}

std::string MyClass::value_string(values v)
{
    return valueMap.find(v)->second;
}
