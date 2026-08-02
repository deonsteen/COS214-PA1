#include "AggregateByRegionStep.h"

AggregateByRegionStep::AggregateByRegionStep() : Transformation("aggregate")
{
}

Transformation *AggregateByRegionStep::clone() const
{
    return new AggregateByRegionStep();
}

std::vector<std::string> AggregateByRegionStep::apply(const std::vector<std::string> &records)
{
    std::vector<std::string> result;
    result.push_back("COUNT=" + std::to_string(records.size()));
    return result;
}
