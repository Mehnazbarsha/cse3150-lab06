#include <iostream>
#include <climits>
#include "fractions.h"

static int passed = 0, failed = 0;

#define EXPECT_EQ(an, ad, en, ed, label)                                    \
    do {                                                                     \
        if ((an) == (en) && (ad) == (ed)) {                                 \
            std::cout << "[PASS] " << label << "\n"; ++passed;              \
        } else {                                                             \
            std::cout << "[FAIL] " << label << "  got " << (an) << "/"      \
                      << (ad) << "  expected " << (en) << "/" << (ed) << "\n";\
            ++failed;                                                        \
        }                                                                    \
    } while(0)

void test_bigint_basics() {
    std::cout << "\n=== bigint basic arithmetic ===\n";

    bigint a("12345678901234567890"), b("98765432109876543210");
    bool ok = (a + b == bigint("111111111011111111100"));
    std::cout << (ok ? "[PASS]" : "[FAIL]") << " bigint large add\n";
    ok ? ++passed : ++failed;

    bool mok = (bigint("999") * bigint("999") == bigint("998001"));
    std::cout << (mok ? "[PASS]" : "[FAIL]") << " bigint 999*999 = 998001\n";
    mok ? ++passed : ++failed;
}

void test_bigfrac_product() {
    std::cout << "\n=== BigFrac product ===\n";

    auto r1 = product(BigFrac{bigint(1LL), bigint(2LL)}, BigFrac{bigint(2LL), bigint(3LL)});
    EXPECT_EQ(r1.first, r1.second, bigint(1LL), bigint(3LL), "(1/2)*(2/3)=1/3");

    auto r2 = product(BigFrac{bigint(3LL), bigint(4LL)}, BigFrac{bigint(8LL), bigint(9LL)});
    EXPECT_EQ(r2.first, r2.second, bigint(2LL), bigint(3LL), "(3/4)*(8/9)=2/3");

    auto r3 = product(BigFrac{bigint("100000000000"), bigint(3LL)}, BigFrac{bigint(3LL), bigint("100000000000")});
    EXPECT_EQ(r3.first, r3.second, bigint(1LL), bigint(1LL), "large cancels to 1/1");

    auto r4 = product(BigFrac{bigint(0LL), bigint(5LL)}, BigFrac{bigint(7LL), bigint(3LL)});
    EXPECT_EQ(r4.first, r4.second, bigint(0LL), bigint(1LL), "(0/5)*(7/3)=0/1");
}

void test_bigfrac_sum() {
    std::cout << "\n=== BigFrac sum ===\n";

    auto r1 = sum(BigFrac{bigint(1LL), bigint(2LL)}, BigFrac{bigint(1LL), bigint(3LL)});
    EXPECT_EQ(r1.first, r1.second, bigint(5LL), bigint(6LL), "(1/2)+(1/3)=5/6");

    auto r2 = sum(BigFrac{bigint(3LL), bigint(4LL)}, BigFrac{bigint(1LL), bigint(4LL)});
    EXPECT_EQ(r2.first, r2.second, bigint(1LL), bigint(1LL), "(3/4)+(1/4)=1");

    auto r3 = sum(BigFrac{bigint(1LL), bigint(6LL)}, BigFrac{bigint(1LL), bigint(6LL)});
    EXPECT_EQ(r3.first, r3.second, bigint(1LL), bigint(3LL), "(1/6)+(1/6)=1/3");

    auto r4 = sum(BigFrac{bigint(1LL), bigint("1000000000")}, BigFrac{bigint(1LL), bigint("1000000000")});
    EXPECT_EQ(r4.first, r4.second, bigint(1LL), bigint("500000000"), "large denom sum reduces");
}

void test_int_overflow_demo() {
    std::cout << "\n=== int overflow demonstration ===\n";

    auto ir = product(IntFrac{100000, 1}, IntFrac{100000, 1});
    auto br = product(BigFrac{bigint(100000LL), bigint(1LL)}, BigFrac{bigint(100000LL), bigint(1LL)});

    bool int_overflowed = (ir.first != (long long)100000 * 100000);
    bool big_correct    = (br.first == bigint(10000000000LL));

    std::cout << (int_overflowed ? "[PASS]" : "[FAIL]") << " int overflows for 100000*100000\n";
    int_overflowed ? ++passed : ++failed;
    std::cout << (big_correct ? "[PASS]" : "[FAIL]") << " bigint correct for 100000*100000\n";
    big_correct ? ++passed : ++failed;

    auto ir2 = sum(IntFrac{INT_MAX, 2}, IntFrac{1, 2});
    auto br2  = sum(BigFrac{bigint((long long)INT_MAX), bigint(2LL)}, BigFrac{bigint(1LL), bigint(2LL)});

    bigint exact_n = (bigint((long long)INT_MAX) + bigint(1LL)) / bigint(2LL);
    bool sum_ok = (br2.first == exact_n && br2.second == bigint(1LL));

    std::cout << (sum_ok ? "[PASS]" : "[FAIL]") << " bigint sum(INT_MAX/2 + 1/2) = " << exact_n << "/1\n";
    sum_ok ? ++passed : ++failed;
}

void test_intfrac_correct() {
    std::cout << "\n=== IntFrac and LLFrac (no overflow) ===\n";

    auto r1 = product(IntFrac{2,3}, IntFrac{3,4});
    EXPECT_EQ(r1.first, r1.second, 1, 2, "IntFrac (2/3)*(3/4)=1/2");

    auto r2 = sum(IntFrac{1,4}, IntFrac{1,4});
    EXPECT_EQ(r2.first, r2.second, 1, 2, "IntFrac (1/4)+(1/4)=1/2");

    auto r3 = sum(LLFrac{5,6}, LLFrac{1,6});
    EXPECT_EQ(r3.first, r3.second, 1LL, 1LL, "LLFrac (5/6)+(1/6)=1");
}

int main() {
    std::cout << "==============================\n";
    std::cout << "  BigInt Fraction Unit Tests  \n";
    std::cout << "==============================\n";

    test_bigint_basics();
    test_bigfrac_product();
    test_bigfrac_sum();
    test_int_overflow_demo();
    test_intfrac_correct();

    std::cout << "\n------------------------------\n";
    std::cout << "Results: " << passed << " passed, " << failed << " failed\n";
    std::cout << "------------------------------\n";

    return failed == 0 ? 0 : 1;
}