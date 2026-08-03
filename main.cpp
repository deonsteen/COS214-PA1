#include <iostream>
#include <string>

// Task 5 includes:

// Task 1
#include "ConnectorFactory.h"
#include "PostgresFactory.h"


// Task 2
#include "Transformation.h"
#include "DeduplicateStep.h"
#include "AggregateByRegionStep.h"
#include "TransformationRegistry.h"

// Task 3 & 4
#include "Pipeline.h"
#include "BatchPipeline.h"
#include "CheckpointManager.h"

// Task 5 includes end.

// Additional testing:

#include "RestApiFactory.h"

//#include "test_framework.h"
//#include "task3_tests.h"
//#include "task2_tests.h"

//TestStats g_stats;

int main() {


    // Additional testing:


    /*
    runTask2Tests();

    std::cout << std::endl;

    runTask3Tests();

    std::cout << std::endl;

    std::cout << "\n=== Summary ===\n";
    std::cout << g_stats.passed << " passed, " << g_stats.failed << " failed\n";

    */

    // Task 1 testing :

    std::cout << "Task1 testing:" << std::endl;

    ConnectorFactory* pgFactory = new PostgresFactory();
    Connector* pgConnector = pgFactory->createConnector();
    std::cout << "Connector source: " << pgConnector->getSource() << std::endl;
    std::vector<std::string> pgData = pgConnector->extract();
    std::cout << "Extracted Records (" << pgData.size() << "):" << std::endl;
    delete pgConnector;
    delete pgFactory;

    std::cout << std::endl;

    // Task 4 testing :

    std::cout << "Task 4 testing:" <<std::endl;

    ConnectorFactory* factory = new PostgresFactory();
    Pipeline* pipeline = new BatchPipeline(factory);
    CheckpointManager manager;

    RunCheckpoint* cp1 = pipeline->createCheckpoint();
    std::cout << "Checkpoint 1 -> Stage: " << cp1->getStage()
              << ", Records: " << cp1->getRecords().size() << "\n";
    manager.save(cp1);

    RunCheckpoint* restoredCp = manager.undo();
    if (restoredCp != nullptr) {
        pipeline->restore(restoredCp);
        std::cout << "restored state into Pipeline!\n";
        delete restoredCp;
    }

    RunCheckpoint* emptyCheck = manager.undo();
    if (emptyCheck == nullptr) {
        std::cout << "Empty history, nullptr returned.\n";
    }

    delete pipeline;

    std::cout << std::endl;

    // Additional testing end.



    std::cout << "Task 5:" << std::endl;

    // Task 5 testing:

    // step 1:
    TransformationRegistry registry;
    registry.registerStep("dedup", new DeduplicateStep());
    registry.registerStep("aggregate", new AggregateByRegionStep());

    // step 2:
    PostgresFactory* PGFactory = new PostgresFactory();
    BatchPipeline* Pipeline = new BatchPipeline(PGFactory);

    // step 3:
    Transformation* clonedDedup = registry.create("dedup");
    Transformation* clonedAggregate = registry.create("aggregate");
    if (clonedDedup != nullptr) {
        Pipeline->addStep(clonedDedup);
    }
    if (clonedAggregate != nullptr) {
        Pipeline->addStep(clonedAggregate);
    }

    // step 4:
    CheckpointManager Manager;

    // step 5:
    Pipeline->run();
    RunCheckpoint* cp = Pipeline->createCheckpoint();
    Manager.save(cp);

    // step 6:
    delete Pipeline;

    return 0;
    }
