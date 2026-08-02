#include "RestApiFactory.h"
#include "RestApiConnector.h"
#include "Connector.h"


Connector *RestApiFactory::createConnector() {

    return new RestApiConnector();
}
