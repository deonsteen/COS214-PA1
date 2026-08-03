#ifndef COS214_PA1_PIPELINE_H
#define COS214_PA1_PIPELINE_H

#include <string>
#include <vector>

#include "ConnectorFactory.h"
#include "Transformation.h"

class RunCheckpoint;

class Pipeline
{

protected:
    ConnectorFactory *factory;
    std::vector<Transformation *> steps;
    int stage;
    std::vector<std::string> records;

public:
    Pipeline(ConnectorFactory *factory);
    virtual ~Pipeline();

    // Template method: fixes the lifecycle's order. Not virtual — see 3.5.
    void run();

    void addStep(Transformation *step);

    RunCheckpoint *createCheckpoint();
    void restore(RunCheckpoint *checkpoint);

protected:
    void connect();
    virtual void extract() = 0;
    void transform();
    virtual void load() = 0;
};

#endif // COS214_PA1_PIPELINE_H
