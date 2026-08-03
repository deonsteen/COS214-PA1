#ifndef COS214_PA1_AGGREGATEBYREGIONSTEP_H
#define COS214_PA1_AGGREGATEBYREGIONSTEP_H

#include "Transformation.h"

class AggregateByRegionStep : public Transformation
{

public:
    AggregateByRegionStep();

    virtual Transformation *clone() const;
    virtual std::vector<std::string> apply(const std::vector<std::string> &records);
};

#endif // COS214_PA1_AGGREGATEBYREGIONSTEP_H
