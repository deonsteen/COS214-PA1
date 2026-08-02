#include "RestApiConnector.h"

RestApiConnector::RestApiConnector() : Connector("restapi") {
}

RestApiConnector::~RestApiConnector() {
}

std::vector<std::string> RestApiConnector::extract() {
    std::vector<std::string> result;
    result.push_back("API:44");
    result.push_back("API:45");
    result.push_back("API:45");
    return result;
}
