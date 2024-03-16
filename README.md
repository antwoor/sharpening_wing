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
    git clone https://github.com/antwoor/sharpening_wing.git
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
1. source python scripts for different trajectories
    ```sh
    cd ~/moveit_ws/src/moveit_solid_robot/src
    python3 tokenizer.py
    python3 rotator.py
    python3 unirotator.py
    ```
2. change links in .cpp files of moveit_solid_robot/src to yours
   example
   from
   ```
   std::ifstream infile("/home/antwoor/moveit_ws/src/moveit_solid_robot/src/merged_df.txt");
   ```
   to
   ```
   std::ifstream infile("/home/$(USER_NAME)/moveit_ws/src/moveit_solid_robot/src/merged_df.txt");
4. source setup.$(YOUR_SHELL_NAME):
    ```sh
    
    source ~/moveit/devel/setup.bash
    ```

5. Launch package with any granted .launch file:
    ```sh
    roslaunch moveit_solid_robot demo_cutter_launch
    ```

6. open new terminal and run trajectory command
   ```sh
   rosrun moveit_solid_robot trajectory_4
   ```
   
## Author
antwoor



