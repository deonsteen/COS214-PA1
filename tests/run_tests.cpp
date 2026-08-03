#include <iostream>

#include "task2_tests.h"
#include "task3_tests.h"
#include "test_framework.h"

TestStats g_stats;

int main()
{
    runTask2Tests();
    runTask3Tests();

    std::cout << "\n=== Summary ===\n";
    std::cout << g_stats.passed << " passed, " << g_stats.failed << " failed\n";

    return g_stats.failed == 0 ? 0 : 1;
}
