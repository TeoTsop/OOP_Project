//All of the enums

#pragma once

//The four cardinal directions
enum Direction {SOUTH,
                NORTH,
                EAST,
                WEST};

//The speed states an object can be
enum SpeedState {STOPPED,
                 HALF_SPEED,
                 FULL_SPEED
                };

//All possible objects in the grid
enum ObjectType {AUTONOMUS_VEHICLE,
                 MOVING_CAR,
                 STOPPED_CAR,
                 MOVING_BIKE,
                 TRAFFIC_SIGN,
                 TRAFFIC_LIGHT
                };

//All traffic colors
enum TrafficLightColor {RED,
                        YELLOW,
                        GREEN};