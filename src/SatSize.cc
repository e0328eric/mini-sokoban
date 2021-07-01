#include <cstdint>

#include "SatSize.hh"

SatSize::SatSize(size_t n)
    : mN(n)
{
}

SatSize::operator size_t() const
{
    return mN;
}

SatSize& SatSize::operator++()
{
    mN = mN > SIZE_MAX ? mN : mN + 1;
    return *this;
}

SatSize& SatSize::operator--()
{
    mN = mN == 0 ? 0 : mN - 1;
    return *this;
}

SatSize SatSize::operator++(int)
{
    SatSize tmp(mN);
    mN = mN > SIZE_MAX ? mN : mN + 1;
    return tmp;
}

SatSize SatSize::operator--(int)
{
    SatSize tmp(mN);
    mN = mN == 0 ? 0 : mN - 1;
    return tmp;
}

bool SatSize::operator==(const SatSize& rhs) const
{
    return mN == rhs.mN;
}

bool SatSize::operator!=(const SatSize& rhs) const
{
    return mN != rhs.mN;
}
