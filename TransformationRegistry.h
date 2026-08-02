#ifndef COS214_PA1_TRANSFORMATIONREGISTRY_H
#define COS214_PA1_TRANSFORMATIONREGISTRY_H

#include <map>
#include <string>

#include "Transformation.h"

class TransformationRegistry
{

private:
    std::map<std::string, Transformation *> prototypes;

public:
    ~TransformationRegistry();

    void registerStep(std::string key, Transformation *prototype);
    Transformation *create(const std::string &key) const;
};

#endif // COS214_PA1_TRANSFORMATIONREGISTRY_H
