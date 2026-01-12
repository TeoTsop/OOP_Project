CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude

TARGET = simulation

SRC = \
src/main.cpp \
src/world/GridWorld.cpp \
src/world/WorldObject.cpp \
src/world/MovingObject.cpp \
src/world/StaticObject.cpp \
src/objects/MovingCar.cpp \
src/objects/MovingBike.cpp \
src/objects/TrafficSign.cpp \
src/objects/TrafficLight.cpp \
src/objects/StationaryVehicle.cpp \
src/common/utils.cpp 

OBJ = $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	del /Q $(OBJ) $(TARGET)