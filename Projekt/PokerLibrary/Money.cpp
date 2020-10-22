#include "pch.h"
#include "Money.h"
#include "Output.h"

const std::array<int, nr_chipvalues> chipstack::values = { 5, 10, 20, 50, 100, 500 };

chipstack::chipstack() {

}
chipstack::chipstack(std::array<int, nr_chipvalues> chips) {
    m_chips = chips;
    checkForNegativeSum();
}


chipstack& chipstack::operator+(const chipstack& a) const
{
	chipstack& result = *(new chipstack());
    for (int i = 0; i < m_chips.size(); i++) {
        result.m_chips[i] = this->m_chips[i] + a.m_chips[i];
    }
    return result; 
}

chipstack& chipstack::operator-(const chipstack& a) const
{
    chipstack& result = *(new chipstack());
    bool allowed = true;
    for (int i = 0; i < m_chips.size(); i++) {
        result.m_chips[i] = this->m_chips[i] - a.m_chips[i];

    }
    result.checkForNegativeSum();
    return result;
}

bool chipstack::operator<=(const chipstack& a) const //compare by sum
{
    return this->sum() <= a.sum();
}

bool chipstack::operator<(const int& a) const //compare a with sum
{
    return this->sum() < a;
}

bool chipstack::operator>(const chipstack& a) const //compare by sum
{
    return this->sum() > a.sum();
}

bool chipstack::operator==(const int& a) const //compare with sum
{
    return this->sum() == a;
}

int chipstack::sum() const
{
    int s = 0;
    for (int i = 0; i < nr_chipvalues; i++) {
        s += values[i] * m_chips[i];
    }
    return s;
}

chipstack chipstack::readChipstackFromConsole()
{
    Output out;
    chipstack c;
    for (int i = 0; i < c.m_chips.size(); i++) {
        c.m_chips[i] = out.readChip(values[i]);
    }
    return c;
}

std::string chipstack::toString() const
{
    std::string s = "{ ";
    for (int i = 0; i < nr_chipvalues; i++) {
        s.append(std::to_string(values[i]));
        s.append("€: ");
        s.append(std::to_string(m_chips[i]));
        i < (nr_chipvalues - 1) ? s.append(", ") : s.append(" }");
    }
    return s;
}

void chipstack::checkForNegativeSum()
{
    if (containsNegatives() && tryRepair() == false) {
        isNegative = true;
        m_chips = { 0 };
    }
}

bool chipstack::containsNegatives() const
{
    bool cont = false;
    for (int i : m_chips) {
        if (i < 0) {
            cont = true;
        }
    }
    return cont;
}

bool chipstack::tryRepair()
{
    bool success = false;
    if (sum() < 0) {
        success = false;
    }
    else {
        int valueCombined = sum();
        int amountForValue = 0;
        for (int i = m_chips.size() - 1; i >= 0; i--) {
            //go through values from big to small and attempt to resort
            amountForValue = valueCombined / values[i];
            valueCombined -= amountForValue * values[i];
            m_chips[i] = amountForValue;
        }
        success = true;
    }
    return success;
}
