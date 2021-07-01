#ifndef _SOKOBAN_PAIR_HH_
#define _SOKOBAN_PAIR_HH_

template <typename T, typename U = T>
class Pair
{
 public:
    Pair(T fst, U snd)
        : fst(fst)
        , snd(snd)
    {
    }

    Pair addf(T n)
    {
        return Pair(fst + n, snd);
    }

    Pair adds(U n)
    {
        return Pair(fst, snd + n);
    }

    Pair subf(T n)
    {
        return Pair(fst - n, snd);
    }

    Pair subs(U n)
    {
        return Pair(fst, snd - n);
    }

 public:
    T fst;
    U snd;
};

#endif// _SOKOBAN_PAIR_HH_
