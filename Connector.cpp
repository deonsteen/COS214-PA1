#include "Connector.h"

Connector::Connector(std::string source){
    this->source = source;
}

Connector::~Connector() {
    // no dynamic memory was allocated in constructor
}

std::string Connector::getSource() const {
    return this->source;
}