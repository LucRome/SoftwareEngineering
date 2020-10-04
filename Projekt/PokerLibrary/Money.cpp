#include "pch.h"
#include "Money.h"

chipstack& chipstack::operator+(const chipstack& a)
{
    chipstack result = chipstack();
    for (int i = 0; i < m_chips.size(); i++) {
        result.m_chips[i] = this->m_chips[i] + a.m_chips[i];
    }
    return result; // keine Ahnung ob des so passt, aber VS wollte da einen Rückgabewert, sonst hätte es nicht Compilt
}
