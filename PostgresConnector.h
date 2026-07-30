#ifndef COS214_PA1_POSTGRESCONNECTOR_H
#define COS214_PA1_POSTGRESCONNECTOR_H

#include "Connector.h"

class PostgresConnector: public Connector {

public:
    virtual std::vector<std::string>extract();
};


#endif //COS214_PA1_POSTGRESCONNECTOR_H
