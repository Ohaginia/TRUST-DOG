#include <ros/ros.h>
#include <tf2_ros/transform_listener.h>
#include <tf/transform_broadcaster.h>
#include <geometry_msgs/TransformStamped.h>
#include <visualization_msgs/Marker.h>
#include <geometry_msgs/Pose.h>
#include <math.h>
#include <std_msgs/Float32MultiArray.h>

void GetQuaternionMsg( double roll, double pitch, double yaw, geometry_msgs::Quaternion &q);
const float l1=0.16;
const float l2=0.16;
double roll=0;
double pitch=0;
double yow=0;
geometry_msgs::Quaternion quat;
visualization_msgs::Marker target;

void target_marker_cb(const std_msgs::Float32MultiArray& target_point)
{
    target.pose.position.x=target_point.data[0]; // target x
    target.pose.position.y=target_point.data[1]; // target y
    target.pose.position.z=target_point.data[2]; //target z
    target.header.stamp = ros::Time::now();
    target.lifetime = ros::Duration();
}

int main(int argc, char** argv){
  ros::init(argc, argv, "ik_movable_area");

  ros::NodeHandle nh;

  ros::Publisher target_marker_pub = nh.advertise<visualization_msgs::Marker>("target_marker", 1);
  ros::Subscriber target_sub = nh.subscribe("target_point", 10, target_marker_cb);

    GetQuaternionMsg(roll , pitch ,yow, quat);
    target.header.frame_id = "leg4";
    target.ns = "basic_shapes";
    target.type = visualization_msgs::Marker::SPHERE;
    target.scale.x = 0.05;
    target.scale.y = 0.05;
    target.scale.z = 0.05;
    target.pose.orientation.x = quat.x;
    target.pose.orientation.y = quat.y;
    target.pose.orientation.z = quat.z;
    target.pose.orientation.w = quat.w;
    target.color.r = 1.0f;
    target.color.g = 0.0f;
    target.color.b = 0.0f;
    target.color.a = 2.0f;
    target.id = 0;
    target.action = visualization_msgs::Marker::ADD;

  ros::Rate rate(10.0);
  while (nh.ok()){
    target_marker_pub.publish(target);

    rate.sleep();
  }
  return 0;
};

void GetQuaternionMsg( double roll, double pitch, double yaw, geometry_msgs::Quaternion &q){
   tf::Quaternion quat=tf::createQuaternionFromRPY(roll,pitch,yaw);
   quaternionTFToMsg(quat,q);
}

