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

add_executable(motor src/motor_node.cpp)
target_link_libraries(motor 
	${catkin_LIBRARIES} 
	${WIRINGPI_LIBRARY}
	motorlib
)
add_dependencies(motor wiringPi)

add_library(encoderlib
	src/encoder.cpp
)

add_executable(encoder src/encoder_node.cpp)
target_link_libraries(encoder 
	${catkin_LIBRARIES} 
	${WIRINGPI_LIBRARY}
	encoderlib
)
add_dependencies(encoderlib wiringPi)

