#ifndef COS214_PA1_CHECKPOINTMANAGER_H
#define COS214_PA1_CHECKPOINTMANAGER_H

#include <string>
#include <vector>
#include "../RunCheckpoint.h"

class CheckpointManager {

private:
    std::vector<RunCheckpoint*> history;

public:
    CheckpointManager();
    void save(RunCheckpoint* save);
    RunCheckpoint* undo();
    ~CheckpointManager();
};


#endif //COS214_PA1_CHECKPOINTMANAGER_H
