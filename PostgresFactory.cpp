#include "PostgresFactory.h"
#include "PostgresConnector.h"

Connector *PostgresFactory::createConnector()
{
Connector* PostgresFactory::createConnector() {
    return new PostgresConnector();
}
