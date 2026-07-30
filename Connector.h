#ifndef COS214_PA1_CONNECTOR_H
#define COS214_PA1_CONNECTOR_H

#include <iostream>
#include <string>
#include <vector>

class Connector {

protected:
    std::string source;

public:
    Connector(std::string source);
    virtual ~Connector();
    virtual std::vector<std::string> extract() = 0;
    std::string getSource() const;
};

#endif //COS214_PA1_CONNECTOR_H
