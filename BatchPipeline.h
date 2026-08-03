#ifndef COS214_PA1_BATCHPIPELINE_H
#define COS214_PA1_BATCHPIPELINE_H

#include "Pipeline.h"

class BatchPipeline : public Pipeline
{

public:
    BatchPipeline(ConnectorFactory *factory);

protected:
    virtual void extract();
    virtual void load();
};

#endif // COS214_PA1_BATCHPIPELINE_H
