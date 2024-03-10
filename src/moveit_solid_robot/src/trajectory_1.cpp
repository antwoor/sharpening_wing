#include <moveit/move_group_interface/move_group_interface.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
const double tau = 2 * M_PI;
int main(int argc, char** argv) {
    ros::init(argc, argv, "moveit_trajectory_planning");
    ros::NodeHandle node_handle;
    ros::AsyncSpinner spinner(1);
    spinner.start();
    static const std::string PLANNING_GROUP = "full_arm_group";
    moveit::planning_interface::MoveGroupInterface move_group(PLANNING_GROUP);
    // класс JointModelGroup используется для взаимодействия с группами движения в Moveit
    // создадим указатель на объект этого класса, в котором будет ссылка на текущее занчение обобщённых координат нашего робота
    const moveit::core::JointModelGroup* p_JOINT_MODEL_GROUP = move_group.getCurrentState()->getJointModelGroup(PLANNING_GROUP);
    // Определите точки, по которым должен пройти робот
    std::vector<geometry_msgs::Pose> trajectory;
    tf2::Quaternion orientation;
    orientation.setRPY(tau/4, 0, 0);
    geometry_msgs::Pose target_pose1;
    // Настройте target_pose1                   
    target_pose1.orientation = tf2::toMsg(orientation); //ZERO INIT VALS
    target_pose1.position.x = -0.035555;                     //Xpos -0.035555
    target_pose1.position.y = -0.18707;                     //Ypos -0.18707
    target_pose1.position.z = 0.34496;                      //Zpos 0.34496
    //target_pose1.orientation.x = 0.68367;             //Xori 0.68367
    //target_pose1.orientation.y = -0.18074;            //Yori -0.18074
    //target_pose1.orientation.z = 0.1604;              //Zori 0.1604
    //target_pose1.orientation.w = 0.68862;             //Wori 0.68862
    
    // Настройте target_pose2

    // Установите целевые позы для планирования
    move_group.setPoseTarget(target_pose1);

    // Выполните планирование траектории
    moveit::planning_interface::MoveGroupInterface::Plan my_plan;
    move_group.plan(my_plan);
    move_group.move();
    
    //move_group.execute(my_plan);

    ros::shutdown();
    return 0;
}
