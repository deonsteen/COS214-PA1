# Local verification suite for Task 2 and Task 3. Not part of the graded
# submission (which is restricted to vector/string/iostream/map) -- keep
# this directory out of the archive you zip for FitchFork.

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g -I..
TARGET = run_tests

SRC = ../Connector.cpp ../ConnectorFactory.cpp \
      ../PostgresConnector.cpp ../RestApiConnector.cpp ../CsvConnector.cpp \
      ../PostgresFactory.cpp ../RestApiFactory.cpp ../CsvFactory.cpp \
      ../Transformation.cpp ../TransformationRegistry.cpp \
      ../DeduplicateStep.cpp ../AggregateByRegionStep.cpp \
      ../Pipeline.cpp ../BatchPipeline.cpp ../StreamingPipeline.cpp

TEST_SRC = task2_tests.cpp task3_tests.cpp run_tests.cpp

all: $(TARGET)
	./$(TARGET)

$(TARGET): $(SRC) $(TEST_SRC) test_framework.h task2_tests.h task3_tests.h
	$(CXX) $(CXXFLAGS) $(SRC) $(TEST_SRC) -o $(TARGET)

asan: CXXFLAGS += -fsanitize=address,undefined
asan: clean $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all clean asan
