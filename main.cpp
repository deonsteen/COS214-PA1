#include <iostream>
#include <vector>
#include <string>

#include "../Pipeline.h"
#include "../RunCheckpoint.h"
#include "CheckpointManager.h"

int main() {
    std::cout << "========================================\n";
    std::cout << "    COS214 PA1 - Task 4 Test Suite     \n";
    std::cout << "========================================\n\n";

    CheckpointManager manager;
    Pipeline pipeline;

    // 1. Create initial checkpoint from Pipeline
    RunCheckpoint* cp1 = pipeline.createCheckpoint();
    std::cout << "Checkpoint 1 created -> Stage: " << cp1->getStage()
              << ", Records count: " << cp1->getRecords().size() << "\n";

    // Save to Caretaker
    manager.save(cp1);

    // 2. Perform an Undo
    RunCheckpoint* restoredCp = manager.undo();
    if (restoredCp != nullptr) {
        // Pass checkpoint back to originator to restore state
        pipeline.restore(restoredCp);
        std::cout << "Successfully restored state into Pipeline!\n";
        delete restoredCp; // Clean up retrieved checkpoint
    }

    // 3. Perform Undo when stack/history is empty
    RunCheckpoint* emptyCheck = manager.undo();
    if (emptyCheck == nullptr) {
        std::cout << "Empty history handled safely (nullptr returned).\n";
    }

    std::cout << "\n========================================\n";
    std::cout << "         All tests completed!           \n";
    std::cout << "========================================\n";

    return 0;
}