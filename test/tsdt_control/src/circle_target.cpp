#include <ros/ros.h>
#include <std_msgs/Float32MultiArray.h>
#include <math.h>

std_msgs::Float32MultiArray circle_target;

int main(int argc, char** argv){
  ros::init(argc, argv, "circle_target");
  ros::NodeHandle nh;
  ros::Publisher target_pub = nh.advertise<std_msgs::Float32MultiArray>("target_point", 1);
  ros::Rate rate(10.0);
  circle_target.data.resize(3);
  int count=0;
  while (nh.ok()){
    circle_target.data[0]=0;
    circle_target.data[1]=0.1*sin(count*0.1);
    circle_target.data[2]=0.1*cos(count*0.1)+0.16;
    target_pub.publish(circle_target);
    ros::spinOnce();
    count++;
    rate.sleep();
  }
  return 0;
};
