#include <iostream>
#include <chrono>
#include <vector>
#include <utility>
#include "fractions.h"

using namespace std;
using namespace chrono;

long long timeUs(auto fn) {
    auto s = high_resolution_clock::now();
    fn();
    auto e = high_resolution_clock::now();
    return duration_cast<microseconds>(e - s).count();
}

long long timeIntProduct(int iters) {
    IntFrac a{3, 4}, b{5, 7}, r{1,1};
    return timeUs([&]{ for (int i = 0; i < iters; ++i) r = product(a, b); });
}

long long timeLLProduct(int iters) {
    LLFrac a{3LL, 4LL}, b{5LL, 7LL}, r{1LL,1LL};
    return timeUs([&]{ for (int i = 0; i < iters; ++i) r = product(a, b); });
}

long long timeBigProduct(int iters) {
    BigFrac a{bigint(3LL), bigint(4LL)}, b{bigint(5LL), bigint(7LL)}, r{bigint(1LL), bigint(1LL)};
    return timeUs([&]{ for (int i = 0; i < iters; ++i) r = product(a, b); });
}

long long timeIntProductOF(int iters) {
    IntFrac a{100000, 3}, b{100000, 7}, r{1,1};
    return timeUs([&]{ for (int i = 0; i < iters; ++i) r = product(a, b); });
}

long long timeLLProductOF(int iters) {
    LLFrac a{100000LL, 3LL}, b{100000LL, 7LL}, r{1LL,1LL};
    return timeUs([&]{ for (int i = 0; i < iters; ++i) r = product(a, b); });
}

long long timeBigProductOF(int iters) {
    BigFrac a{bigint(100000LL), bigint(3LL)}, b{bigint(100000LL), bigint(7LL)}, r{bigint(1LL), bigint(1LL)};
    return timeUs([&]{ for (int i = 0; i < iters; ++i) r = product(a, b); });
}

void showOverflowFailure() {
    IntFrac  ia{100000, 3}, ib{100000, 7};
    LLFrac   la{100000LL, 3LL}, lb{100000LL, 7LL};
    BigFrac  ba{bigint(100000LL), bigint(3LL)}, bb{bigint(100000LL), bigint(7LL)};

    auto ir = product(ia, ib);
    auto lr = product(la, lb);
    auto br = product(ba, bb);

    cout << "\n=== Where int-based fractions fail ===\n";
    cout << "  product(100000/3, 100000/7):\n";
    cout << "    int    result: " << ir.first << " / " << ir.second << "  <-- WRONG (overflow)\n";
    cout << "    long   result: " << lr.first << " / " << lr.second << "\n";
    cout << "    bigint result: " << br.first << " / " << br.second << "\n";

    IntFrac  is_a{2147483647, 2}, is_b{1, 2};
    LLFrac   ls_a{2147483647LL, 2LL}, ls_b{1LL, 2LL};
    BigFrac  bs_a{bigint(2147483647LL), bigint(2LL)}, bs_b{bigint(1LL), bigint(2LL)};

    auto isr = sum(is_a, is_b);
    auto lsr = sum(ls_a, ls_b);
    auto bsr = sum(bs_a, bs_b);

    cout << "\n  sum(INT_MAX/2, 1/2) = (INT_MAX+1)/2 = 2^30:\n";
    cout << "    int    result: " << isr.first << " / " << isr.second << "  <-- WRONG (overflow in cross-multiply)\n";
    cout << "    long   result: " << lsr.first << " / " << lsr.second << "\n";
    cout << "    bigint result: " << bsr.first << " / " << bsr.second << "\n";
}

int main() {
    vector<int> iters = {10, 100, 1000, 10000, 100000};

    cout << "=== Non-overflow: pair<T,T> product timing (microseconds) ===\n";
    cout << "iterations\tpair<int,int>\tpair<long,long>\tpair<bigint,bigint>\n";
    for (int n : iters)
        cout << n << "\t\t" << timeIntProduct(n) << "\t\t" << timeLLProduct(n) << "\t\t" << timeBigProduct(n) << "\n";

    cout << "\n=== Overflow-range: pair<T,T> product timing (microseconds) ===\n";
    cout << "(int overflows for these values — results invalid for int)\n";
    cout << "iterations\tpair<int,int>\tpair<long,long>\tpair<bigint,bigint>\n";
    for (int n : iters)
        cout << n << "\t\t" << timeIntProductOF(n) << "\t\t" << timeLLProductOF(n) << "\t\t" << timeBigProductOF(n) << "\n";

    showOverflowFailure();
    return 0;
}