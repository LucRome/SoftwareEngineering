#include "pch.h"
#include "Money.h"
#include "Output.h"

chipstack& chipstack::operator+(const chipstack& a)
{
	chipstack& result = *(new chipstack());
    for (int i = 0; i < m_chips.size(); i++) {
        result.m_chips[i] = this->m_chips[i] + a.m_chips[i];
    }
    return result; 
}

chipstack& chipstack::operator-(const chipstack& a)
{
	chipstack& result = *(new chipstack());
	for (int i = 0; i < m_chips.size(); i++) {
		result.m_chips[i] = this->m_chips[i] - a.m_chips[i];
	}
	return result; 
}

chipstack chipstack::readChipstackFromConsole()
{
    Output out;
    chipstack c;
    int val;
    for (int i = 0; i < c.m_chips.size(); i++) {
        val = c.m_chips[i];
        val = out.readChip(chipvalues(i));
    }
    return c;
}
