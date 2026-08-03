#include "Connector.h"

Connector::Connector(std::string source) : source(source)
{
}

Connector::~Connector()
{
    // no dynamic memory owned by the base class
}

std::string Connector::getSource() const
{
    return this->source;
}
Connector::Connector(const std::string& source){
    this->source = source;
}

std::string Connector::getSource() const {
    return this->source;
}
