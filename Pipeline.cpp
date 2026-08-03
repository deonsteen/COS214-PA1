#include "Pipeline.h"

#include <iostream>

#include "Connector.h"

Pipeline::Pipeline(ConnectorFactory *factory) : factory(factory), stage(0)
{
}

Pipeline::~Pipeline()
{
    delete factory;

    for (size_t i = 0; i < steps.size(); ++i)
    {
        delete steps[i];
    }
}

void Pipeline::addStep(Transformation *step)
{
    if (step == nullptr)
    {
        return;
    }

    steps.push_back(step);
}

void Pipeline::run()
{
    connect();
    extract();
    transform();
    load();
}

void Pipeline::connect()
{
    Connector *connector = factory->createConnector();
    std::cout << "Connecting to " << connector->getSource() << "\n";
    stage = 1;
    delete connector;
}

void Pipeline::transform()
{
    for (size_t i = 0; i < steps.size(); ++i)
    {
        records = steps[i]->apply(records);
    }

    stage = 3;
}
