#ifndef COS214_PA1_RUNCHECKPOINT_H
#define COS214_PA1_RUNCHECKPOINT_H

#include <vector>
#include <string>

class RunCheckpoint {

private:
    int stage;
    std::vector<std::string> records;

public:
    RunCheckpoint(int stage, const std::vector<std::string>& records);
    virtual ~RunCheckpoint();
    int getStage() const;
    std::vector<std::string> getRecords();
};


#endif //COS214_PA1_RUNCHECKPOINT_H
