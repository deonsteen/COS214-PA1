#include "DeduplicateStep.h"

DeduplicateStep::DeduplicateStep() : Transformation("dedup")
{
}

Transformation *DeduplicateStep::clone() const
{
    return new DeduplicateStep();
}

std::vector<std::string> DeduplicateStep::apply(const std::vector<std::string> &records)
{
    std::vector<std::string> result;

    for (size_t i = 0; i < records.size(); ++i)
    {
        if (result.empty() || result.back() != records[i])
        {
            result.push_back(records[i]);
        }
    }

    return result;
}
