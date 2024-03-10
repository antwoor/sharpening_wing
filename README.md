# This pacakge provides the tool for creating preview animation of sharpening wings! 

## Description
  to use it with your wing you must have the wing_sheet.csv with all the needed information  
  (rename or modify your sheet if it`s needed)
## requirements
- ROS (Robot Operating System) noetic
- wstool

## Installation
1. Clone the repository into your catkin home directory:
    ```sh
    cd ~/
    git clone <repository link>
    cd moveit_ws

    ```

2. Install package dependencies using rosdep:
    ```sh
    cd ~/moveit_ws
    rosdep install --from-paths src --ignore-src -r -y
    ```

3. Compile the package:
    ```sh
    catkin init
    catkin build
    ```

## Usage
1. source setup.$(YOUR_SHELL_NAME):
    ```sh
    source ~/moveit/devel/setup.bash
    ```

2. Launch package with any granted .launch file:
    ```sh
    roslaunch moveit_solid_robot demo_cutter_launch
    ```

3. open new terminal and run trajectory command
   ```sh
   rosrun moveit_solid_robot trajectory_4
   ```
   
## Author
antwoor



