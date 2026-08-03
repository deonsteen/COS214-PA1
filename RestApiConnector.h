#ifndef COS214_PA1_RESTAPICONNECTOR_H
#define COS214_PA1_RESTAPICONNECTOR_H

#include "Connector.h"

class RestApiConnector : public Connector
{

public:
    RestApiConnector();

    virtual std::vector<std::string> extract();
};

#endif // COS214_PA1_RESTAPICONNECTOR_H
