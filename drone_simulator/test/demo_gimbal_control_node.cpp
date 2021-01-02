#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <sensor_msgs/Joy.h>
#include <tf2/LinearMath/Matrix3x3.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>

using nav_msgs::Odometry;
using nav_msgs::OdometryConstPtr;
using sensor_msgs::Joy;
using sensor_msgs::JoyConstPtr;

ros::Publisher gimbal_cmd_pub;

int cnt=0, freq_ctrl=0;

void odomCb(const OdometryConstPtr& odom)
{
    if(++cnt < freq_ctrl)
        return;
    cnt = 0;

    tf2::Quaternion iQb;
    tf2::fromMsg(odom->pose.pose.orientation, iQb);
    tf2Scalar roll, pitch, yaw;
    tf2::Matrix3x3(iQb).getEulerYPR(yaw, pitch, roll);
    Joy gimbal_cmd;
    gimbal_cmd.header.stamp = ros::Time::now();
    gimbal_cmd.axes.push_back(0.0f);
    gimbal_cmd.axes.push_back(-roll);
    gimbal_cmd.axes.push_back(-pitch);
    gimbal_cmd_pub.publish(gimbal_cmd);
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "demo_gimbal_control");
    ros::NodeHandle nh;
    ros::param::param<int>("~div", freq_ctrl, 2);
    gimbal_cmd_pub = nh.advertise<Joy>("gimbal_angle_cmd", 1);
    ros::Subscriber attitude_sub = nh.subscribe<Odometry>("hil_odom", 1, odomCb);
    ros::spin();
    return 0;
}