#ifndef COS214_PA1_CONNECTORFACTORY_H
#define COS214_PA1_CONNECTORFACTORY_H

#include "Connector.h"

class ConnectorFactory {

    public:
    virtual ~ConnectorFactory();
    virtual Connector* createConnector() =0;
};


#endif //COS214_PA1_CONNECTORFACTORY_H
