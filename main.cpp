#include <iostream>
#include <string>

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

int main() {

    // step 1:
    TransformationRegistry registry;
    registry.registerStep("dedup", new DeduplicateStep());
    registry.registerStep("aggregate", new AggregateByRegionStep());

    // step 2:
    PostgresFactory* pgFactory = new PostgresFactory();
    BatchPipeline* pipeline = new BatchPipeline(pgFactory);

    // step 3:
    Transformation* clonedDedup = registry.create("dedup");
    Transformation* clonedAggregate = registry.create("aggregate");
    if (clonedDedup != nullptr) {
        pipeline->addStep(clonedDedup);
    }
    if (clonedAggregate != nullptr) {
        pipeline->addStep(clonedAggregate);
    }

    // step 4:
    CheckpointManager manager;

    // step 5:
    pipeline->run();
    RunCheckpoint* cp = pipeline->createCheckpoint();
    manager.save(cp);

    // step 6:
    delete pipeline;

    return 0;
    }