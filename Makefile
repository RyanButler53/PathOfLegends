CXX = clang++
CXXFLAGS = --std=c++2a -g -Wextra -pedantic #-O3

TARGET = pathSim

all:$(TARGET)

pathSim: pathSim.o simulation.o hashQueue.o player.o
	$(CXX) -o pathSim pathSim.o hashQueue.o player.o simulation.o

pathSim.o: player.hpp hashQueue.cpp pathSim.cpp
	$(CXX) $(CXXFLAGS) -c pathSim.cpp

player.o: player.hpp player.cpp
	$(CXX) $(CXXFLAGS) -c player.cpp

hashQueue.o: hashQueue.cpp hashQueue.hpp player.hpp
	$(CXX) $(CXXFLAGS) -c hashQueue.cpp

simulation.o: hashQueue.hpp player.hpp simulation.cpp simulation.hpp
	$(CXX) $(CXXFLAGS) -c simulation.cpp

clean: 
	rm -rf *.o $(TARGET)