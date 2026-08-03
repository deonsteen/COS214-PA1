#ifndef COS214_PA1_POSTGRESFACTORY_H
#define COS214_PA1_POSTGRESFACTORY_H

#include "ConnectorFactory.h"

class PostgresFactory : public ConnectorFactory
{

public:
    virtual Connector *createConnector();
};

#endif // COS214_PA1_POSTGRESFACTORY_H
class PostgresFactory : public ConnectorFactory {

public:
    virtual Connector* createConnector() override;
};


#endif //COS214_PA1_POSTGRESFACTORY_H
