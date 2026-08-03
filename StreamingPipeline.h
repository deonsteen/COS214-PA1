#ifndef COS214_PA1_STREAMINGPIPELINE_H
#define COS214_PA1_STREAMINGPIPELINE_H

#include "Pipeline.h"

class StreamingPipeline : public Pipeline
{

public:
    StreamingPipeline(ConnectorFactory *factory);

protected:
    virtual void extract();
    virtual void load();
};

#endif // COS214_PA1_STREAMINGPIPELINE_H
