

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g
TARGET = engine

OBJS = Connector.o PostgresConnector.o RestApiConnector.o CsvConnector.o ConnectorFactory.o PostgresFactory.o RestApiFactory.o CsvFactory.o main.o
all: $(TARGET)
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean