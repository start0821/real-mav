#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <geometry_msgs/TwistStamped.h>
#include <geometry_msgs/PoseStamped.h>

// geometry_msgs::PoseWithCovarianceStamped odommsg;
geometry_msgs::PoseStamped posemsg;
geometry_msgs::TwistStamped twistmsg;
nav_msgs::Odometry odometrymsg;
int freq;
void msgCallback(const nav_msgs::Odometry::ConstPtr& msg){
    // ROS_INFO("Seq: [%d]", msg->header.seq);
    // ROS_INFO("Position-> x: [%f], y: [%f], z: [%f]", msg->pose.pose.position.x,msg->pose.pose.position.y, msg->pose.pose.position.z);
    // ROS_INFO("Orientation-> x: [%f], y: [%f], z: [%f], w: [%f]", msg->pose.pose.orientation.x, msg->pose.pose.orientation.y, msg->pose.pose.orientation.z, msg->pose.pose.orientation.w);
    // ROS_INFO("Vel-> Linear: [%f], Angular: [%f]", msg->twist.twist.linear.x,msg->twist.twist.angular.z);

    // odommsg.header.seq = msg->header.seq;
    twistmsg.header.seq = msg->header.seq;
    posemsg.header.seq = msg->header.seq;
    
    // odommsg.pose.covariance = msg->pose.covariance;
    // odommsg.pose.pose.position.x = msg->pose.pose.position.x;
    // odommsg.pose.pose.position.y = msg->pose.pose.position.y;
    // odommsg.pose.pose.position.z = msg->pose.pose.position.z;
    // odommsg.pose.pose.orientation.x = msg->pose.pose.orientation.x;
    // odommsg.pose.pose.orientation.y = msg->pose.pose.orientation.y;
    // odommsg.pose.pose.orientation.z = msg->pose.pose.orientation.z;
    // odommsg.pose.pose.orientation.w = msg->pose.pose.orientation.w;

    posemsg.pose.position.x = msg->pose.pose.position.x;
    posemsg.pose.position.y = msg->pose.pose.position.y;
    posemsg.pose.position.z = msg->pose.pose.position.z;
    posemsg.pose.orientation.x = msg->pose.pose.orientation.x;
    posemsg.pose.orientation.y = msg->pose.pose.orientation.y;
    posemsg.pose.orientation.z = msg->pose.pose.orientation.z;
    posemsg.pose.orientation.w = msg->pose.pose.orientation.w;

    twistmsg.twist.linear.x = msg->twist.twist.linear.x;
    twistmsg.twist.linear.y = msg->twist.twist.linear.y;
    twistmsg.twist.linear.z = msg->twist.twist.linear.z;

    twistmsg.twist.angular.x = msg->twist.twist.angular.x;
    twistmsg.twist.angular.y = msg->twist.twist.angular.y;
    twistmsg.twist.angular.z = msg->twist.twist.angular.z;
    
    
}

int main(int argc, char **argv){
    ros::init(argc,argv,"subscribe_realsense_pubish_mavros");
    ros::NodeHandle nh;
    ros::Publisher mavros_mocap_pub = nh.advertise<geometry_msgs::PoseStamped>("mavros/vision_pose/pose",100);
    // ros::Publisher mavros_pose_pub = nh.advertise<geometry_msgs::PoseWithCovarianceStamped>("mavros/vision_pose/pose_cov",100);
    ros::Publisher mavros_speed_pub = nh.advertise<geometry_msgs::TwistStamped>("mavros/vision_speed/speed_twist",100);
    ros::Subscriber realsesne_sub = nh.subscribe("camera/odom/sample",100,msgCallback);
    nh.setParam("vision_freq",20);


    while(ros::ok()){
        nh.getParam("vision_freq",freq);
        ros::Rate loop_rate(freq);
        std::string child,frame;
        nh.getParam("mavros/vision_pose/tf/frame_id",frame);
        // odommsg.header.stamp = ros::Time::now();
        twistmsg.header.stamp = ros::Time::now();
        //posemsg.header.stamp = ros::Time::now();
        posemsg.header.stamp = ros::Time::now()-ros::Duration(10);
        posemsg.header.frame_id="map";
        // odommsg.header.frame_id=frame;
        twistmsg.header.frame_id=frame;
        ros::spinOnce();
        mavros_mocap_pub.publish(posemsg);
        // mavros_pose_pub.publish(odommsg);
        mavros_speed_pub.publish(twistmsg);
        loop_rate.sleep();
    }

    return 0;
}
