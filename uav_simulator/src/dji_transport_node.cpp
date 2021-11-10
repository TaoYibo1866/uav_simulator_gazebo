#include <ros/ros.h>
#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <geometry_msgs/PointStamped.h>
#include <geometry_msgs/QuaternionStamped.h>
#include <nav_msgs/Odometry.h>

using geometry_msgs::PointStamped;
using geometry_msgs::QuaternionStamped;
using geometry_msgs::PointStampedConstPtr;
using geometry_msgs::QuaternionStampedConstPtr;
using nav_msgs::Odometry;
using message_filters::sync_policies::ApproximateTime;

typedef ApproximateTime<PointStamped, QuaternionStamped> SyncPolicy;

ros::Publisher odom_pub;

void stateCallback(const PointStampedConstPtr& local_position, const QuaternionStampedConstPtr& attitude)
{
    Odometry odom;
    odom.header.stamp = attitude->header.stamp;
    odom.pose.pose.position = local_position->point;
    odom.pose.pose.orientation = attitude->quaternion;
    odom_pub.publish(odom);
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "dji_transport");
    ros::NodeHandle nh;
    odom_pub = nh.advertise<Odometry>("hil_odom", 1);
    message_filters::Subscriber<PointStamped> local_position_sub(nh, "local_position", 1);
    message_filters::Subscriber<QuaternionStamped> attitude_sub(nh, "attitude", 1);
    message_filters::Synchronizer<SyncPolicy> sync(SyncPolicy(10), local_position_sub, attitude_sub);
    sync.registerCallback(boost::bind(&stateCallback, _1,_2));
    ros::spin();
    return 0;
}