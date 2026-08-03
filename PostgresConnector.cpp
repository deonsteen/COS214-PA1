#include "PostgresConnector.h"

PostgresConnector::PostgresConnector() : Connector("postgres")
{
}

std::vector<std::string> PostgresConnector::extract()
{
PostgresConnector::PostgresConnector() : Connector("postgres") {
}

PostgresConnector::~PostgresConnector() {
}

std::vector<std::string> PostgresConnector::extract() {
    std::vector<std::string> result;
    result.push_back("PG:001");
    result.push_back("PG:002");
    result.push_back("PG:002");
    result.push_back("PG:003");
    return result;
}
}
