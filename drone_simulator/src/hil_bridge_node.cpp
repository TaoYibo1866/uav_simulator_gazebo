#include <ros/ros.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include <tf2/LinearMath/Transform.h>
#include <nav_msgs/Odometry.h>
#include <gazebo_msgs/ModelState.h>

using nav_msgs::Odometry;
using nav_msgs::OdometryConstPtr;
using gazebo_msgs::ModelState;

int freq_ctrl=1, cnt=0;
double x_offset, y_offset, z_offset, yaw_offset;
ModelState state_msg;
ros::Publisher model_state_pub;

void odomCb(const OdometryConstPtr& odom)
{
    if(++cnt < freq_ctrl)
        return;
    cnt = 0;

    tf2::Vector3 origin;
    tf2::Quaternion rotation;
    tf2::fromMsg(odom->pose.pose.position, origin);
    tf2::fromMsg(odom->pose.pose.orientation, rotation);
    tf2::Transform iTw, iTb, wTb;
    iTw.setOrigin(tf2::Vector3(x_offset, y_offset, z_offset));
    iTw.setRotation(tf2::Quaternion(tf2::Vector3(0, 0, 1), yaw_offset));
    iTb.setOrigin(origin);
    iTb.setRotation(rotation);
    wTb = iTw.inverse() * iTb;
    tf2::toMsg(wTb, state_msg.pose);
    model_state_pub.publish(state_msg);
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "hil_bridge");
    ros::NodeHandle nh("~");
    ros::param::param<std::string>("~model_name", state_msg.model_name, "dji_m100");
    ros::param::param<int>("~div", freq_ctrl, 1);
    ros::param::param<double>("~x_offset", x_offset, 0);
    ros::param::param<double>("~y_offset", y_offset, 0);
    ros::param::param<double>("~z_offset", z_offset, 0);
    ros::param::param<double>("~yaw_offset", yaw_offset, 0);
    ros::Subscriber odom_sub = nh.subscribe<Odometry>("odometry", 1, odomCb);
    state_msg.reference_frame = "world";
    model_state_pub = nh.advertise<ModelState>("/gazebo/set_model_state", 1);
    ros::spin();
    return 0;
}