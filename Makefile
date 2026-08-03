CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic
OBJS = main.o \
       Connector.o PostgresConnector.o RestApiConnector.o CsvConnector.o \
       ConnectorFactory.o PostgresFactory.o RestApiFactory.o CsvFactory.o \
       Transformation.o DeduplicateStep.o AggregateByRegionStep.o TransformationRegistry.o \
       Pipeline.o BatchPipeline.o StreamingPipeline.o \
       RunCheckpoint.o CheckpointManager.o

TARGET = engine

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGET)