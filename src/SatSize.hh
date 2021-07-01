#ifndef _SOKOBAN_SATSIZE_T_
#define _SOKOBAN_SATSIZE_T_

#include <cstddef>

class SatSize
{
 public:
    SatSize(size_t n);

    operator size_t() const;

    SatSize& operator++();
    SatSize& operator--();
    SatSize operator++(int);
    SatSize operator--(int);
    bool operator==(const SatSize& rhs) const;
    bool operator!=(const SatSize& rhs) const;

 private:
    size_t mN;
};

#endif// _SOKOBAN_SATSIZE_T_
