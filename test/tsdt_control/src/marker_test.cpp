#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <geometry_msgs/Pose.h>
#include <tf/transform_broadcaster.h>

#include <string>
#include <math.h>

void GetQuaternionMsg( double roll, double pitch, double yaw, geometry_msgs::Quaternion &q);
int main(int argc, char** argv)
{
  ros::init(argc, argv, "marker_test");
  ros::NodeHandle nh;

  // publisher
  ros::Publisher marker_pub = nh.advertise<visualization_msgs::Marker>("marker", 1);

  ros::Rate loop_rate(10);
  double roll=90*M_PI/180;
  double pitch=0*M_PI/180;
  double yow=0;
  geometry_msgs::Quaternion quat;
  GetQuaternionMsg(roll , pitch ,yow, quat);
  while (ros::ok())
  {
    visualization_msgs::Marker marker;
    marker.header.frame_id = "/world";
    marker.header.stamp = ros::Time::now();
    marker.ns = "basic_shapes";
    marker.id = 0;

    marker.type = visualization_msgs::Marker::CYLINDER;
    marker.action = visualization_msgs::Marker::ADD;
    marker.lifetime = ros::Duration();

    marker.scale.x = 0.5;
    marker.scale.y = 0.5;
    marker.scale.z = 0.0;
    marker.pose.position.x = 0;
    marker.pose.position.y = 0;
    marker.pose.position.z = 0;
    marker.pose.orientation.x = quat.x;
    marker.pose.orientation.y = quat.y;
    marker.pose.orientation.z = quat.z;
    marker.pose.orientation.w = quat.w;
    marker.color.r = 0.0f;
    marker.color.g = 1.0f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0f;
    marker_pub.publish(marker);

    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}

void GetQuaternionMsg( double roll, double pitch, double yaw, geometry_msgs::Quaternion &q){
   tf::Quaternion quat=tf::createQuaternionFromRPY(roll,pitch,yaw);
   quaternionTFToMsg(quat,q);
}
