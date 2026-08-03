#include "BatchPipeline.h"

#include <iostream>

#include "Connector.h"

BatchPipeline::BatchPipeline(ConnectorFactory *factory) : Pipeline(factory)
{
}

void BatchPipeline::extract()
{
    Connector *connector = factory->createConnector();
    records = connector->extract();
    std::cout << "Batch extract: " << records.size() << " records\n";
    stage = 2;
    delete connector;
}

void BatchPipeline::load()
{
    std::cout << "Batch load: " << records.size() << " records written\n";
    stage = 4;
}
