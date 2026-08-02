#ifndef COS214_PA1_DEDUPLICATESTEP_H
#define COS214_PA1_DEDUPLICATESTEP_H

#include "Transformation.h"

class DeduplicateStep : public Transformation
{

public:
    DeduplicateStep();

    virtual Transformation *clone() const;
    virtual std::vector<std::string> apply(const std::vector<std::string> &records);
};

#endif // COS214_PA1_DEDUPLICATESTEP_H
