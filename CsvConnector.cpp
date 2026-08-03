#include "CsvConnector.h"

CsvConnector::CsvConnector() : Connector("csv") {
}

CsvConnector::~CsvConnector() {
}

std::vector<std::string> CsvConnector::extract() {
    std::vector<std::string> result;
    result.push_back("CSV:x1");
    result.push_back("CSV:x2");
    result.push_back("CSV:x3");
    result.push_back("CSV:x3");
    return result;
}