cmake_minimum_required(VERSION 2.8.3)
project(pi_plattform)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  nav_msgs
  roscpp
  rospy
  sensor_msgs
  std_msgs
)

FIND_LIBRARY(WIRINGPI_LIBRARY wiringPi /home/pi/wiringPi)
FIND_LIBRARY(HC-SR04_LIBRARY sonarLib /home/pi/libs/HC-SR04-Raspberry-Pi-C-)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES pi_plattform
#  CATKIN_DEPENDS geometry_msgs nav_msgs roscpp rospy sensor_msgs std_msgs
#  DEPENDS system_lib
)


## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)


add_library(motorlib
	src/motor.cpp
)

add_executable(motor_node src/motor_node.cpp)
target_link_libraries(motor_node 
	${catkin_LIBRARIES} 
	${WIRINGPI_LIBRARY}
	motorlib
)
add_dependencies(motor_node wiringPi)

add_library(encoderlib
	src/encoder.cpp
)

add_executable(encoder_node src/encoder_node.cpp)
target_link_libraries(encoder_node 
	${catkin_LIBRARIES} 
	${WIRINGPI_LIBRARY}
	encoderlib
)
add_dependencies(encoder_node wiringPi)

add_executable(motorcontroll_node src/motorcontroll_node.cpp)
target_link_libraries(motorcontroll_node 
	${catkin_LIBRARIES} 
	
)
#add_dependencies(motorcontroll_node wiringPi)

add_executable(sonar_node src/HC-SR04_node.cpp)
target_link_libraries(encoder_node 
	${catkin_LIBRARIES} 
	${WIRINGPI_LIBRARY}
	${HC-SR04_LIBRARY}
)
add_dependencies(encoder_node wiringPi sonarLib)


