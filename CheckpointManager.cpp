#include "../CheckpointManager.h"

CheckpointManager::CheckpointManager() {

}

CheckpointManager::~CheckpointManager() {

    for (size_t i = 0; i < history.size(); i++) {
        delete history[i];
    }
    history.clear();
}

void CheckpointManager::save(RunCheckpoint *save) {

    if (save != nullptr) {
        history.push_back(save);
    }
}

RunCheckpoint *CheckpointManager::undo() {

    if (history.empty()) {
        return nullptr;
    }

    RunCheckpoint* save = history.back();
    history.pop_back();
    return save;
}
