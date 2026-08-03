#include "StreamingPipeline.h"

#include <iostream>

#include "Connector.h"

StreamingPipeline::StreamingPipeline(ConnectorFactory *factory) : Pipeline(factory)
{
}

void StreamingPipeline::extract()
{
    Connector *connector = factory->createConnector();
    records = connector->extract();
    std::cout << "Streaming extract: " << records.size() << " records\n";
    stage = 2;
    delete connector;
}

void StreamingPipeline::load()
{
    std::cout << "Streaming load: " << records.size() << " records streamed\n";
    stage = 4;
}
