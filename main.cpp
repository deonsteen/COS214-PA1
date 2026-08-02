#include <iostream>
#include <vector>

#include "ConnectorFactory.h"
#include "CsvFactory.h"
#include "PostgresFactory.h"
#include "RestApiFactory.h"

void testFactory(ConnectorFactory* factory) {
    // 1. Create product using the factory
    Connector* connector = factory->createConnector();

    // 2. Output connector details
    std::cout << "--- Testing Connector [Source: " << connector->getSource() << "] ---" << std::endl;

    // 3. Extract data records
    std::vector<std::string> data = connector->extract();
    std::cout << "Extracted Records (" << data.size() << "):" << std::endl;
    for (size_t i = 0; i < data.size(); ++i) {
        std::cout << "  - " << data[i] << std::endl;
    }
    std::cout << std::endl;

    // 4. Clean up dynamically allocated product memory
    delete connector;
}

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "     COS214 PA1 - Task 1 Factory Test    " << std::endl;
    std::cout << "========================================\n" << std::endl;

    // Instantiate factories
    ConnectorFactory* csvFactory = new CsvFactory();
    ConnectorFactory* pgFactory = new PostgresFactory();
    ConnectorFactory* apiFactory = new RestApiFactory();

    // Test each factory
    testFactory(csvFactory);
    testFactory(pgFactory);
    testFactory(apiFactory);

    // Clean up factory memory
    delete csvFactory;
    delete pgFactory;
    delete apiFactory;

    std::cout << "All Task 1 factories created and cleaned up successfully!" << std::endl;

    return 0;
}