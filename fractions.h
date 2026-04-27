#pragma once
#include <utility>
#include <stdexcept>
#include "bigint.h"

inline long long gcd_ll(long long a, long long b) {
    a = a < 0 ? -a : a;
    b = b < 0 ? -b : b;
    while (b) { a %= b; std::swap(a, b); }
    return a ? a : 1;
}

inline bigint gcd_big(bigint a, bigint b) {
    if (a < bigint(0LL)) a = bigint(0LL) - a;
    if (b < bigint(0LL)) b = bigint(0LL) - b;
    while (b != bigint(0LL)) { bigint t = a % b; a = b; b = t; }
    return (a == bigint(0LL)) ? bigint(1LL) : a;
}

using IntFrac  = std::pair<int, int>;
using LLFrac   = std::pair<long long, long long>;
using BigFrac  = std::pair<bigint, bigint>;

inline IntFrac reduce(IntFrac f) {
    long long g = gcd_ll(f.first, f.second);
    return { (int)(f.first / g), (int)(f.second / g) };
}

inline LLFrac reduce(LLFrac f) {
    long long g = gcd_ll(f.first, f.second);
    return { f.first / g, f.second / g };
}

inline BigFrac reduce(BigFrac f) {
    bigint g = gcd_big(f.first, f.second);
    return { f.first / g, f.second / g };
}

inline IntFrac product(const IntFrac& lhs, const IntFrac& rhs) {
    return reduce(IntFrac{ lhs.first * rhs.first, lhs.second * rhs.second });
}

inline LLFrac product(const LLFrac& lhs, const LLFrac& rhs) {
    return reduce(LLFrac{ lhs.first * rhs.first, lhs.second * rhs.second });
}

inline BigFrac product(const BigFrac& lhs, const BigFrac& rhs) {
    return reduce(BigFrac{ lhs.first * rhs.first, lhs.second * rhs.second });
}

inline IntFrac sum(const IntFrac& lhs, const IntFrac& rhs) {
    return reduce(IntFrac{
        lhs.first * rhs.second + rhs.first * lhs.second,
        lhs.second * rhs.second
    });
}

inline LLFrac sum(const LLFrac& lhs, const LLFrac& rhs) {
    return reduce(LLFrac{
        lhs.first * rhs.second + rhs.first * lhs.second,
        lhs.second * rhs.second
    });
}

inline BigFrac sum(const BigFrac& lhs, const BigFrac& rhs) {
    return reduce(BigFrac{
        lhs.first * rhs.second + rhs.first * lhs.second,
        lhs.second * rhs.second
    });
}
