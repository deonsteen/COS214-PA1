#include "Connector.h"

Connector::Connector(const std::string& source){
    this->source = source;
}

std::string Connector::getSource() const {
    return this->source;
}