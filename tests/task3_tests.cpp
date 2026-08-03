#include "task3_tests.h"
#include "test_framework.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../AggregateByRegionStep.h"
#include "../BatchPipeline.h"
#include "../CsvFactory.h"
#include "../DeduplicateStep.h"
#include "../PostgresFactory.h"
#include "../RestApiFactory.h"
#include "../StreamingPipeline.h"

using std::string;
using std::vector;

namespace
{

// White-box test helpers: Pipeline's stage/records are protected by design
// (external code has no business touching lifecycle state). A subclass
// defined only here, in the test file, can read those inherited protected
// members without changing the graded Pipeline.h/BatchPipeline.h at all.
class InspectableBatchPipeline : public BatchPipeline
{
public:
    explicit InspectableBatchPipeline(ConnectorFactory *factory) : BatchPipeline(factory) {}
    int getStage() const { return stage; }
    vector<string> getRecords() const { return records; }
};

class InspectableStreamingPipeline : public StreamingPipeline
{
public:
    explicit InspectableStreamingPipeline(ConnectorFactory *factory) : StreamingPipeline(factory) {}
    int getStage() const { return stage; }
    vector<string> getRecords() const { return records; }
};

// Runs pipeline.run() with std::cout redirected into a string so the exact
// printed lifecycle messages can be asserted on.
string captureRun(Pipeline &pipeline)
{
    std::ostringstream capture;
    std::streambuf *old = std::cout.rdbuf(capture.rdbuf());
    pipeline.run();
    std::cout.rdbuf(old);
    return capture.str();
}

void testBatchPipelineNoSteps()
{
    std::cout << "-- BatchPipeline + PostgresFactory, no steps --\n";

    InspectableBatchPipeline pipeline(new PostgresFactory());
    string output = captureRun(pipeline);

    check(output.find("Connecting to postgres\n") != string::npos, "prints \"Connecting to postgres\"");
    check(output.find("Batch extract: 4 records\n") != string::npos, "prints \"Batch extract: 4 records\" (raw Postgres extract)");
    check(output.find("Batch load: 4 records written\n") != string::npos, "prints \"Batch load: 4 records written\" (no steps: nothing removed)");

    size_t posConnect = output.find("Connecting");
    size_t posExtract = output.find("Batch extract");
    size_t posLoad = output.find("Batch load");
    check(posConnect < posExtract && posExtract < posLoad, "run() executes connect -> extract -> load in that order");

    check(pipeline.getStage() == 4, "stage reaches 4 once run() completes");
    check(pipeline.getRecords().size() == 4, "records left untouched with zero transformation steps");
}

void testBatchPipelineDedupOnly()
{
    std::cout << "-- BatchPipeline + PostgresFactory + dedup --\n";

    InspectableBatchPipeline pipeline(new PostgresFactory());
    pipeline.addStep(new DeduplicateStep());
    string output = captureRun(pipeline);

    // Postgres raw: {"PG:001","PG:002","PG:002","PG:003"} (4)
    // dedup collapses the consecutive "PG:002","PG:002" -> 3
    check(output.find("Batch load: 3 records written\n") != string::npos,
          "dedup collapses the one consecutive duplicate: 4 raw -> 3 written");
    check(pipeline.getRecords().size() == 3, "records vector holds 3 entries after transform()");
}

void testBatchPipelineDedupThenAggregate()
{
    std::cout << "-- BatchPipeline + PostgresFactory + dedup + aggregate --\n";

    InspectableBatchPipeline pipeline(new PostgresFactory());
    pipeline.addStep(new DeduplicateStep());
    pipeline.addStep(new AggregateByRegionStep());
    string output = captureRun(pipeline);

    // 4 raw -> dedup -> 3 -> aggregate -> {"COUNT=3"} -> 1
    check(output.find("Batch load: 1 records written\n") != string::npos,
          "steps chain in order: dedup then aggregate -> 1 record (\"COUNT=3\")");
    vector<string> records = pipeline.getRecords();
    check(records.size() == 1 && records[0] == "COUNT=3", "final record is exactly \"COUNT=3\"");
}

void testStreamingPipelineNoSteps()
{
    std::cout << "-- StreamingPipeline + RestApiFactory, no steps --\n";

    InspectableStreamingPipeline pipeline(new RestApiFactory());
    string output = captureRun(pipeline);

    check(output.find("Connecting to restapi\n") != string::npos, "prints \"Connecting to restapi\"");
    check(output.find("Streaming extract: 3 records\n") != string::npos, "prints \"Streaming extract: 3 records\" (raw RestApi extract)");
    check(output.find("Streaming load: 3 records streamed\n") != string::npos, "prints \"Streaming load: 3 records streamed\" (no steps)");
}

void testStreamingPipelineDedup()
{
    std::cout << "-- StreamingPipeline + RestApiFactory + dedup --\n";

    InspectableStreamingPipeline pipeline(new RestApiFactory());
    pipeline.addStep(new DeduplicateStep());
    string output = captureRun(pipeline);

    // RestApi raw: {"API:44","API:45","API:45"} (3) -> dedup -> 2
    check(output.find("Streaming load: 2 records streamed\n") != string::npos,
          "dedup collapses the consecutive duplicate: 3 raw -> 2 streamed");
}

void testStreamingPipelineAggregateOnly()
{
    std::cout << "-- StreamingPipeline + RestApiFactory + aggregate --\n";

    InspectableStreamingPipeline pipeline(new RestApiFactory());
    pipeline.addStep(new AggregateByRegionStep());
    string output = captureRun(pipeline);

    // aggregate alone counts the raw 3 records, dedup is not in the chain
    check(output.find("Streaming load: 1 records streamed\n") != string::npos,
          "aggregate alone counts all 3 raw records -> 1 record (\"COUNT=3\")");
    vector<string> records = pipeline.getRecords();
    check(records.size() == 1 && records[0] == "COUNT=3", "final record is exactly \"COUNT=3\"");
}

void testCsvSourceThroughBatchPipeline()
{
    std::cout << "-- BatchPipeline + CsvFactory --\n";

    InspectableBatchPipeline noSteps(new CsvFactory());
    string outputNoSteps = captureRun(noSteps);
    check(outputNoSteps.find("Connecting to csv\n") != string::npos, "prints \"Connecting to csv\"");
    check(outputNoSteps.find("Batch extract: 4 records\n") != string::npos, "prints \"Batch extract: 4 records\" (raw Csv extract)");
    check(outputNoSteps.find("Batch load: 4 records written\n") != string::npos, "no steps: all 4 raw Csv records pass through");

    InspectableBatchPipeline withDedup(new CsvFactory());
    withDedup.addStep(new DeduplicateStep());
    string outputDedup = captureRun(withDedup);
    // Csv raw: {"CSV:x1","CSV:x2","CSV:x3","CSV:x3"} (4) -> dedup -> 3
    check(outputDedup.find("Batch load: 3 records written\n") != string::npos,
          "dedup collapses the trailing consecutive duplicate: 4 raw -> 3 written");
}

void testAddStepIgnoresNull()
{
    std::cout << "-- addStep(nullptr) --\n";

    InspectableBatchPipeline pipeline(new PostgresFactory());
    pipeline.addStep(nullptr);
    string output = captureRun(pipeline);

    check(output.find("Batch load: 4 records written\n") != string::npos,
          "addStep(nullptr) is silently ignored -- pipeline behaves as if it had zero steps");
}

} // namespace

void runTask3Tests()
{
    std::cout << "\n=== Task 3: Pipeline lifecycle ===\n";
    testBatchPipelineNoSteps();
    testBatchPipelineDedupOnly();
    testBatchPipelineDedupThenAggregate();
    testStreamingPipelineNoSteps();
    testStreamingPipelineDedup();
    testStreamingPipelineAggregateOnly();
    testCsvSourceThroughBatchPipeline();
    testAddStepIgnoresNull();
}
