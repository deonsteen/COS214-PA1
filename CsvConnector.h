#ifndef COS214_PA1_CSVCONNECTOR_H
#define COS214_PA1_CSVCONNECTOR_H

#include "Connector.h"

class CsvConnector: public Connector {

    public:
    virtual std::vector<std::string>extract();
};


#endif //COS214_PA1_CSVCONNECTOR_H
