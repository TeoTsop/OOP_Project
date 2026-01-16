CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude

TARGET = simulation.exe

BUILD_DIR = build

SRC = main.cpp \
	  src/common/utils.cpp \
	  src/common/position.cpp \
	  src/world/GridWorld.cpp \
	  src/world/WorldObject.cpp \
	  src/world/MovingObject.cpp \
	  src/world/StaticObject.cpp \
	  src/objects/MovingCar.cpp \
	  src/objects/MovingBike.cpp \
	  src/objects/TrafficSign.cpp \
	  src/objects/TrafficLight.cpp \
	  src/objects/StationaryVehicle.cpp \
	  src/sensors/Sensor.cpp \
	  src/sensors/CameraSensor.cpp \
	  src/sensors/LidarSensor.cpp \
	  src/sensors/RadarSensor.cpp \
	  src/vehicle/SensorFusionEngine.cpp \
 	  src/vehicle/SelfDrivingCar.cpp


OBJ = $(SRC:%.cpp=$(BUILD_DIR)/%.o)

all: $(TARGET)

$(BUILD_DIR):
	@if not exist "$(BUILD_DIR)" mkdir "$(BUILD_DIR)"
	@if not exist "$(BUILD_DIR)\src\world" mkdir "$(BUILD_DIR)\src\world"
	@if not exist "$(BUILD_DIR)\src\objects" mkdir "$(BUILD_DIR)\src\objects"
	@if not exist "$(BUILD_DIR)\src\common" mkdir "$(BUILD_DIR)\src\common"

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET)

$(BUILD_DIR)/%.o: %.cpp
	@if not exist "$(@D)" mkdir "$(@D)"
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@if exist "$(BUILD_DIR)" rmdir /S /Q "$(BUILD_DIR)" 2>nul
	@del /F /Q $(TARGET) 2>nul

rebuild: clean all

.PHONY: all clean rebuild