#ifndef COS214_PA1_POSTGRESCONNECTOR_H
#define COS214_PA1_POSTGRESCONNECTOR_H

#include "Connector.h"

class PostgresConnector : public Connector
{

public:
    PostgresConnector();

    virtual std::vector<std::string> extract();
};

#endif // COS214_PA1_POSTGRESCONNECTOR_H
class PostgresConnector: public Connector {

public:
    PostgresConnector();
    virtual ~PostgresConnector() override;
    virtual std::vector<std::string>extract() override;
};


#endif //COS214_PA1_POSTGRESCONNECTOR_H
