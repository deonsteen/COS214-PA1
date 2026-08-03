#include "TransformationRegistry.h"

TransformationRegistry::~TransformationRegistry()
{
    for (std::map<std::string, Transformation *>::iterator it = prototypes.begin(); it != prototypes.end(); ++it)
    {
        delete it->second;
    }
}

void TransformationRegistry::registerStep(std::string key, Transformation *prototype)
{
    if (prototype == nullptr)
    {
        return;
    }

    std::map<std::string, Transformation *>::iterator it = prototypes.find(key);
    if (it != prototypes.end())
    {
        delete it->second;
        it->second = prototype;
    }
    else
    {
        prototypes[key] = prototype;
    }
}

Transformation *TransformationRegistry::create(const std::string &key) const
{
    std::map<std::string, Transformation *>::const_iterator it = prototypes.find(key);
    if (it == prototypes.end())
    {
        return nullptr;
    }

    return it->second->clone();
}
