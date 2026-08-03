#ifndef COS214_PA1_CSVFACTORY_H
#define COS214_PA1_CSVFACTORY_H

#include "ConnectorFactory.h"

class CsvFactory : public ConnectorFactory
{

public:
    virtual Connector *createConnector();
};

#endif // COS214_PA1_CSVFACTORY_H
class CsvFactory :public ConnectorFactory {

    public:
    virtual Connector* createConnector() override;
};


#endif //COS214_PA1_CSVFACTORY_H
