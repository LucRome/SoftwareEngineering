#include "pch.h"
#include "StringMaps.h"

std::string StringMaps::suit_string(suits s)
{
    return suitMap.find(s)->second;
}

std::string StringMaps::value_string(values v)
{
    return valueMap.find(v)->second;
}
