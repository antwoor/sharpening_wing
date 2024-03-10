#include <moveit/move_group_interface/move_group_interface.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include <fstream>

const double tau = 2 * M_PI;
void planner(std::vector<geometry_msgs::Pose>& path, double w, double  bx, double by, double bz) 
{
    std::ifstream infile("/home/antwoor/moveit_ws/src/moveit_solid_robot/src/merged_df.txt"); // Открыть текстовый файл для чтения
    std::string line;
    tf2::Quaternion ori;
    //ori.setRPY(tau/4, -M_PI/4, 0);
    while (std::getline(infile, line)) { // Считывать строки из файла
        std::istringstream iss(line);
        std::string token;
        geometry_msgs::Pose pose;
        // Разделить строку на составляющие
        std::getline(iss, token, ',');
        pose.position.x = std::stod(token) * w + bx; // Преобразовать строку в double
        std::getline(iss, token, ',');
        pose.position.y = std::stod(token) * w + by; // Преобразовать строку в double
        std::getline(iss, token, ',');
        pose.position.z = std::stod(token) * w + bz; // Преобразовать строку в double
        std::getline(iss, token, ',');
        double pitch = std::stod(token);
        std::getline(iss, token, ',');
        ori.setRPY(tau/4, -(M_PI/4)+ pitch * std::stod(token)*M_PI/180,0); //(M_PI/4)-0.10472,
        pose.orientation = tf2::toMsg(ori); //добавляем дефолтную ориентацию
        path.push_back(pose); // Добавить объект Pose в вектор
    }
}
int main(int argc, char** argv) {
    ros::init(argc, argv, "moveit_trajectory_planning4");
    ros::NodeHandle node_handle;
    ros::AsyncSpinner spinner(1);
    spinner.start();
    static const std::string PLANNING_GROUP = "full_arm_group";
    moveit::planning_interface::MoveGroupInterface move_group(PLANNING_GROUP);
    // Определите точки, по которым должен пройти робот
    std::vector<geometry_msgs::Pose> trajectory;
    //планируем маршрут
    planner(trajectory, 0.0008, -0.052237, -0.20, 0.34908);
    move_group.setPlannerId("RRT");
    moveit::planning_interface::MoveGroupInterface::Plan my_plan;
    for (int i = 0; i < trajectory.size(); i++)
    {
        move_group.setPoseTarget(trajectory[i]);
        move_group.plan(my_plan);
        //move_group.move();
        move_group.execute(my_plan);
    }
    
    for (const auto& pose : trajectory) {
        std::cout << "x: " << pose.position.x << ", y: " << pose.position.y << ", z: " << pose.position.z << std::endl;
    }
    ros::shutdown();
    return 0;
}