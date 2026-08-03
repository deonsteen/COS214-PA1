#ifndef COS214_PA1_PIPELINE_H
#define COS214_PA1_PIPELINE_H
#include "../RunCheckpoint.h"


class Pipeline {

private:
    int stage;
    std::vector<std::string> records;

public:
    Pipeline();
    ~Pipeline();
    RunCheckpoint* createCheckpoint() const;
    void restore(RunCheckpoint*);
};


#endif //COS214_PA1_PIPELINE_H
