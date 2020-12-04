/******ros header*****/
#include <ros/ros.h>
#include <sensor_msgs/JointState.h>
#include <std_msgs/Float32MultiArray.h>
/********************/
#include <string>
#include <math.h>
#define _USE_MATH_DEFINE

float y=0, z=0; //target point
float angle1=0,angle2=0; //set angle
float C1=0, C2=0; //cos1, cos2
float S1=0, S2=0; //sin1, sin2
const float L1=0.16, L2=0.16; //leg length(m)
sensor_msgs::JointState joint_state;

void ik_callback(const std_msgs::Float32MultiArray& target_point)
{
    y=target_point.data[0]; // target y
    z=target_point.data[1]; //target z

    /****Movable area evaluation**********/
    if(!(pow((L1-L2),2.0)<=(pow(z,2.0)+pow(y,2.0))&&(pow(z,2.0)+pow(y,2.0))<=pow((L1+L2),2.0))){
        y=0;
        z=sqrt(pow(L1,2.0)+pow(L2,2.0));
        ROS_WARN("Outside the movable field");
    }

    /********angle2 solution******/
    C2=(pow(z,2.0)+pow(y,2.0)-pow(L1,2.0)-pow(L2,2.0))/(2*L1*L2);
    S2=sqrt(1-pow(C2,2.0));
    angle2=atan2(S2,C2);

    /*******angle1 solution*******/
    C1=(pow(z,2.0)+pow(y,2.0)+pow(L1,2.0)-pow(L2,2.0))/(2*L1*sqrt(pow(L1,2.0)+pow(L2,2.0)));
    S1=sqrt(1-pow(C2,2.0));
    angle1=atan2(y,z)-atan2(S1,C1);

    joint_state.position[0] = -angle1;
    joint_state.position[1] = -angle2;
    
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "pos_to_angle");
    ros::NodeHandle nh;
    ros::Publisher joint_pub = nh.advertise<sensor_msgs::JointState>("joint_states", 10);
    ros::Subscriber target_sub = nh.subscribe("target_point", 10, ik_callback);
    joint_state.name.resize(2);
    joint_state.name[0] = "joint1";
    joint_state.name[1] = "joint2";
    joint_state.position.resize(2);
    
    ros::Rate loop_rate(10);

  while (ros::ok())
  {
        joint_state.header.stamp = ros::Time::now();
        joint_pub.publish(joint_state);
        ros::spinOnce();
        loop_rate.sleep();
  }
  return 0;
}