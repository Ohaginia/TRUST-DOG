#include <ros/ros.h>
#include <tf2_ros/transform_listener.h>
#include <tf/transform_broadcaster.h>
#include <geometry_msgs/TransformStamped.h>
#include <visualization_msgs/Marker.h>
#include <geometry_msgs/Pose.h>
#include <math.h>

void GetQuaternionMsg( double roll, double pitch, double yaw, geometry_msgs::Quaternion &q);
const float l1=0.16;
const float l2=0.16;
double roll=90*M_PI/180;
double pitch=0;
double yow=0;
geometry_msgs::Quaternion quat;

int main(int argc, char** argv){
  ros::init(argc, argv, "ik_movable_area");

  ros::NodeHandle nh;

  ros::Publisher area_pub = nh.advertise<visualization_msgs::Marker>("ik_area", 1);
  tf2_ros::Buffer tfBuffer;
  tf2_ros::TransformListener tfListener(tfBuffer);
    GetQuaternionMsg(roll , pitch ,yow, quat);
    visualization_msgs::Marker ik_area;
    ik_area.type = visualization_msgs::Marker::CYLINDER;
    ik_area.scale.x = 2*(l1+l2);
    ik_area.scale.y = ik_area.scale.x;
    ik_area.scale.z = 0.001;
    ik_area.pose.orientation.x = quat.x;
    ik_area.pose.orientation.y = quat.y;
    ik_area.pose.orientation.z = quat.z;
    ik_area.pose.orientation.w = quat.w;
    ik_area.color.r = 2.0f;
    ik_area.color.g = 2.0f;
    ik_area.color.b = 2.0f;
    ik_area.color.a = 0.3f;

  ros::Rate rate(10.0);
  while (nh.ok()){
    geometry_msgs::TransformStamped transformStamped;
    try{
      transformStamped = tfBuffer.lookupTransform("world", "leg1", ros::Time(0));
    }
    catch (tf2::TransformException &ex) {
      ROS_WARN("%s",ex.what());
      ros::Duration(1.0).sleep();
      continue;
    }
    auto& trans = transformStamped.transform.translation;
    ik_area.header.frame_id = "world";
    ik_area.header.stamp = ros::Time::now();
    ik_area.ns = "basic_shapes";
    ik_area.id = 0;

    ik_area.action = visualization_msgs::Marker::ADD;
    ik_area.lifetime = ros::Duration();

    ik_area.pose.position.x = trans.x;
    ik_area.pose.position.y = trans.y+0.14;
    ik_area.pose.position.z = trans.z;

    area_pub.publish(ik_area);

    rate.sleep();
  }
  return 0;
};

void GetQuaternionMsg( double roll, double pitch, double yaw, geometry_msgs::Quaternion &q){
   tf::Quaternion quat=tf::createQuaternionFromRPY(roll,pitch,yaw);
   quaternionTFToMsg(quat,q);
}

