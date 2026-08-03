#include "task2_tests.h"
#include "test_framework.h"

#include <iostream>
#include <string>
#include <vector>

#include "../AggregateByRegionStep.h"
#include "../DeduplicateStep.h"
#include "../TransformationRegistry.h"

using std::string;
using std::vector;

namespace
{

string join(const vector<string> &records)
{
    string result = "{";
    for (size_t i = 0; i < records.size(); ++i)
    {
        if (i > 0)
        {
            result += ",";
        }
        result += records[i];
    }
    result += "}";
    return result;
}

void testDeduplicateStep()
{
    std::cout << "-- DeduplicateStep --\n";

    DeduplicateStep dedup;
    check(dedup.getName() == "dedup", "name is \"dedup\"");

    vector<string> specExample = {"a", "a", "b", "a"};
    vector<string> expected = {"a", "b", "a"};
    check(dedup.apply(specExample) == expected,
          "apply({\"a\",\"a\",\"b\",\"a\"}) -> " + join(expected) + " (spec example)");

    vector<string> empty;
    check(dedup.apply(empty).empty(), "apply({}) -> {} (empty input)");

    vector<string> single = {"x"};
    check(dedup.apply(single) == single, "apply({\"x\"}) -> {\"x\"} (single element)");

    vector<string> nonConsecutive = {"a", "b", "a"};
    check(dedup.apply(nonConsecutive) == nonConsecutive,
          "apply({\"a\",\"b\",\"a\"}) -> {\"a\",\"b\",\"a\"} (non-consecutive repeats are kept)");

    vector<string> allSame = {"a", "a", "a"};
    vector<string> allSameExpected = {"a"};
    check(dedup.apply(allSame) == allSameExpected, "apply({\"a\",\"a\",\"a\"}) -> {\"a\"} (whole run collapses)");

    Transformation *clone = dedup.clone();
    check(clone != nullptr, "clone() returns non-null");
    check(clone != &dedup, "clone() returns a distinct object, not the same pointer");
    check(clone->getName() == "dedup", "clone keeps name \"dedup\"");
    check(clone->apply(specExample) == expected, "clone behaves identically to the original on apply()");
    delete clone;
}

void testAggregateByRegionStep()
{
    std::cout << "-- AggregateByRegionStep --\n";

    AggregateByRegionStep agg;
    check(agg.getName() == "aggregate", "name is \"aggregate\"");

    vector<string> three = {"r1", "r2", "r3"};
    vector<string> expectedThree = {"COUNT=3"};
    check(agg.apply(three) == expectedThree, "apply(size 3) -> {\"COUNT=3\"} (spec example)");

    vector<string> empty;
    vector<string> expectedZero = {"COUNT=0"};
    check(agg.apply(empty) == expectedZero, "apply({}) -> {\"COUNT=0\"}");

    vector<string> one = {"only"};
    vector<string> expectedOne = {"COUNT=1"};
    check(agg.apply(one) == expectedOne, "apply(size 1) -> {\"COUNT=1\"}");

    Transformation *clone = agg.clone();
    check(clone != nullptr, "clone() returns non-null");
    check(clone != &agg, "clone() returns a distinct object, not the same pointer");
    check(clone->getName() == "aggregate", "clone keeps name \"aggregate\"");
    check(clone->apply(three) == expectedThree, "clone behaves identically to the original on apply()");
    delete clone;
}

void testTransformationRegistry()
{
    std::cout << "-- TransformationRegistry --\n";

    TransformationRegistry registry;
    check(registry.create("dedup") == nullptr, "create() on an unregistered key returns nullptr");

    registry.registerStep("dedup", new DeduplicateStep());
    registry.registerStep("aggregate", new AggregateByRegionStep());

    Transformation *a = registry.create("dedup");
    Transformation *b = registry.create("dedup");
    check(a != nullptr && b != nullptr, "create() on a registered key returns non-null");
    check(a != b, "two create() calls return two distinct clone objects (never the stored prototype)");
    check(a->getName() == "dedup" && b->getName() == "dedup", "clones report the correct name");

    vector<string> input = {"a", "a", "b"};
    vector<string> expected = {"a", "b"};
    check(a->apply(input) == expected, "clone obtained from the registry behaves like its prototype");

    // Overwriting an existing key must free the old prototype before storing
    // the new one -- this only crashes/leaks if registerStep mismanages
    // memory, so it's a meaningful check even though the outward behaviour
    // (still a working "dedup" step) looks the same.
    registry.registerStep("dedup", new DeduplicateStep());
    Transformation *c = registry.create("dedup");
    check(c != nullptr && c->getName() == "dedup",
          "re-registering under an existing key replaces the prototype without breaking create()");

    Transformation *agg = registry.create("aggregate");
    check(agg != nullptr && agg->getName() == "aggregate", "second registered key (\"aggregate\") still resolves correctly");

    delete a;
    delete b;
    delete c;
    delete agg;
    // registry's destructor runs here (end of scope) and must free the two
    // prototypes still stored ("dedup" and "aggregate") -- verified for
    // leaks by running this suite under AddressSanitizer (see tests/Makefile
    // "asan" target), not by an in-code assertion.
}

} // namespace

void runTask2Tests()
{
    std::cout << "\n=== Task 2: Transformations ===\n";
    testDeduplicateStep();
    testAggregateByRegionStep();
    testTransformationRegistry();
}
