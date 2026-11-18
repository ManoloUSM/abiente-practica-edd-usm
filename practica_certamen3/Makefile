CXX = g++
CXXFLAGS = -Wall -Wno-unused-parameter -std=c++11 -g

GRAFOS_DIR = ../grafos
SRCS = main.cpp ejercicios.cpp algoritmos_base.cpp colasp.cpp $(GRAFOS_DIR)/grafo.cpp $(GRAFOS_DIR)/lista.cpp $(GRAFOS_DIR)/cola.cpp
TARGET = test_certamen

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
