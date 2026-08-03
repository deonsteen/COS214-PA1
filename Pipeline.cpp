#include "../Pipeline.h"

Pipeline::Pipeline() {
    this->stage = 0;
}

Pipeline::~Pipeline() {

}

RunCheckpoint* Pipeline::createCheckpoint() const {

    return new RunCheckpoint(this->stage, this->records);
}

void Pipeline::restore(RunCheckpoint* checkpoint) {
    if (checkpoint != nullptr) {
        this->stage = checkpoint->getStage();
        this->records = checkpoint->getRecords();
    }
}