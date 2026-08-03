#ifndef COS214_PA1_TESTS_TEST_FRAMEWORK_H
#define COS214_PA1_TESTS_TEST_FRAMEWORK_H

#include <iostream>
#include <string>

// Minimal, dependency-free check-and-report harness for local verification.
// Not part of the graded submission (only vector/string/iostream/map are
// allowed there) -- this lives in tests/ so it's easy to exclude when
// zipping the files for FitchFork.

struct TestStats
{
    int passed;
    int failed;

    TestStats() : passed(0), failed(0) {}
};

extern TestStats g_stats;

inline void check(bool condition, const std::string &description)
{
    if (condition)
    {
        ++g_stats.passed;
        std::cout << "  [PASS] " << description << "\n";
    }
    else
    {
        ++g_stats.failed;
        std::cout << "  [FAIL] " << description << "\n";
    }
}

#endif // COS214_PA1_TESTS_TEST_FRAMEWORK_H
