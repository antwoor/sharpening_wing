#include <moveit/move_group_interface/move_group_interface.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include <fstream>
const double tau = 2 * M_PI;
void planner(std::vector<geometry_msgs::Pose>& path, double w, double  bx, double by, double bz) 
{
    std::ifstream infile("/home/antwoor/moveit_ws/src/moveit_solid_robot/src/waypoints.txt"); // Открыть текстовый файл для чтения
    std::string line;
    tf2::Quaternion ori;
    ori.setRPY(tau/4, -M_PI/4, 0);
    while (std::getline(infile, line)) { // Считывать строки из файла
        std::istringstream iss(line);
        std::string token;
        geometry_msgs::Pose pose;
        // Разделить строку на составляющие
        std::getline(iss, token, ',');
        pose.position.x = std::stod(token) * w + bx; // Преобразовать строку в double
        std::getline(iss, token, ',');
        pose.position.y = -std::stod(token) * w + by; // Преобразовать строку в double
        std::getline(iss, token, ',');
        pose.position.z = std::stod(token) * w + bz; // Преобразовать строку в double
        pose.orientation = tf2::toMsg(ori); //добавляем дефолтную ориентацию
        path.push_back(pose); // Добавить объект Pose в вектор
    }
}
int main(int argc, char** argv) {
    ros::init(argc, argv, "moveit_trajectory_planning2");
    ros::NodeHandle node_handle;
    ros::AsyncSpinner spinner(1);
    spinner.start();
    static const std::string PLANNING_GROUP = "full_arm_group";
    moveit::planning_interface::MoveGroupInterface move_group(PLANNING_GROUP);
    // класс JointModelGroup используется для взаимодействия с группами движения в Moveit
    // создадим указатель на объект этого класса, в котором будет ссылка на текущее занчение обобщённых координат нашего робота
    // !!!!! ПОПРОБОВАТЬ СТЕРЕТЬ НИЖНЮЮ СТРОЧКУ
    const moveit::core::JointModelGroup* p_JOINT_MODEL_GROUP = move_group.getCurrentState()->getJointModelGroup(PLANNING_GROUP);
    // Определите точки, по которым должен пройти робот
    std::vector<geometry_msgs::Pose> trajectory;
    //std::vector<geometry_msgs::Pose>& road = trajectory;
    //планируем маршрут
    planner(trajectory, 0.001, -0.050555, -0.18707, 0.34496);

    for (int i = 0; i < trajectory.size(); i++)
    {
        move_group.setPoseTarget(trajectory[i]);
        moveit::planning_interface::MoveGroupInterface::Plan my_plan;
        move_group.plan(my_plan);
        move_group.move();
    }
    for (const auto& pose : trajectory) {
        std::cout << "x: " << pose.position.x << ", y: " << pose.position.y << ", z: " << pose.position.z << std::endl;
    }
    ros::shutdown();
    return 0;
}