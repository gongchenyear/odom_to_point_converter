#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/PointStamped.h>

class OdomToPointNode
{
public:
    OdomToPointNode()
    {
        odom_sub_ = nh_.subscribe("odom_in", 1000, &OdomToPointNode::odomCallback, this);
        point_pub_ = nh_.advertise<geometry_msgs::PointStamped>("point_out", 1000);
    }

    void odomCallback(const nav_msgs::Odometry::ConstPtr& msg)
    {
        geometry_msgs::PointStamped point_msg;
        point_msg.header = msg->header;
        point_msg.point = msg->pose.pose.position;
        point_pub_.publish(point_msg);
    }

private:
    ros::NodeHandle nh_;
    ros::Subscriber odom_sub_;
    ros::Publisher point_pub_;
};

int main(int argc, char** argv)
{
    ros::init(argc, argv, "odom_to_point_node");
    OdomToPointNode node;
    ros::spin();
    return 0;
}