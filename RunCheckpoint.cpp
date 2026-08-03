#include "../RunCheckpoint.h"

RunCheckpoint::RunCheckpoint(int stage, const std::vector<std::string>& records) {
    this->stage = stage;
    this->records = records;
}

RunCheckpoint::~RunCheckpoint() {
}

int RunCheckpoint::getStage() const {
    return this->stage;
}

std::vector<std::string> RunCheckpoint::getRecords() {
    return this->records;
}
