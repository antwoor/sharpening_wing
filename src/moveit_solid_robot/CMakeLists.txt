cmake_minimum_required(VERSION 3.1.3)
project(moveit_solid_robot)

find_package(catkin REQUIRED
roscpp
moveit_core
moveit_visual_tools
moveit_ros_planning
moveit_ros_planning_interface
)

catkin_package(
  CATKIN_DEPENDS
    roscpp
    moveit_core
    moveit_visual_tools
    moveit_ros_planning
    moveit_ros_planning_interface
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)
add_executable(trajectory_1 src/trajectory_1.cpp)
add_executable(trajectory_2 src/trajectory_2.cpp)
add_executable(trajectory_3 src/trajectory_3.cpp)
add_executable(trajectory_4 src/trajectory_4.cpp)
target_link_libraries(trajectory_1 ${catkin_LIBRARIES})
target_link_libraries(trajectory_2 ${catkin_LIBRARIES})
target_link_libraries(trajectory_3 ${catkin_LIBRARIES})
target_link_libraries(trajectory_4 ${catkin_LIBRARIES})

install(DIRECTORY launch DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
  PATTERN "setup_assistant.launch" EXCLUDE)
install(DIRECTORY config DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})
