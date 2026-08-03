#include "Transformation.h"

Transformation::Transformation(std::string name) : name(name)
{
}

Transformation::~Transformation()
{
    // no dynamic memory owned by the base class
}

std::string Transformation::getName() const
{
    return this->name;
}
