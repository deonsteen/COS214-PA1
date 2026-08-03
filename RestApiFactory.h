#ifndef COS214_PA1_RESTAPIFACTORY_H
#define COS214_PA1_RESTAPIFACTORY_H

#include "ConnectorFactory.h"

class RestApiFactory : public ConnectorFactory
{

public:
    virtual Connector *createConnector();
};

#endif // COS214_PA1_RESTAPIFACTORY_H
#include "Connector.h"

class RestApiFactory :public ConnectorFactory {

public:
    virtual Connector* createConnector() override;
};


#endif //COS214_PA1_RESTAPIFACTORY_H
