
/***+++++++++++++++++odrive_tool************************/
#include <ODriveTool.h>
// Printing with stream operator helper functions
template<class T> inline Print& operator <<(Print &obj,     T arg) { obj.print(arg);    return obj; }
template<>        inline Print& operator <<(Print &obj, float arg) { obj.print(arg, 4); return obj; }
/*******************ros******************************/
#include <ros.h>
#include <std_msgs/UInt16.h>
#include <sensor_msgs/JointState.h>
#include <std_msgs/Int32MultiArray.h>
#include <std_msgs/Int32.h>
#include <std_msgs/Float32MultiArray.h>
#include <std_msgs/Float32.h>
#include <std_msgs/String.h>
#include <std_msgs/Empty.h>
#include <ros/time.h>
/********************network_config*********************/
#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
const char* ssid = "ohaginia";
const char* password = "Shoma0218";
IPAddress server(192,168,2,4); //ip adress(sh command "ip a")
const uint16_t serverPort = 11411; 
WiFiClient client;
/**********************wifihardware_class********************/
class WiFiHardware {
  public:
  WiFiHardware() {};
  void init() {
    client.connect(server, serverPort); 
    }
  int read() {
    return client.read();   
    }
  void write(uint8_t* data, int length) {
    for(int i=0; i<length; i++)
      client.write(data[i]);
  }
  unsigned long time() {
     return millis();
  }
};
/**************************************************************/
#define LED_BUILTIN 15 //debug led
const int num_motor=2; //motor quantity
const float pi=3.14159262;
const int reducer_rate=8;

ODriveTool odrive(Serial2); //odrive object
void joint_cb(const sensor_msgs::JointState& cmd_msg);   //joint_cb callback function

ros::NodeHandle_<WiFiHardware>  nh; //declared nodehandle
ros::Subscriber<sensor_msgs::JointState> sub("joint_states", joint_cb); //declared subscriber

double joint1_angle=0;
double joint2_angle=0;

void setup() {  
  /********************network_config*********************/
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    delay(5000);
    ESP.restart();
  }
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
  }

  ArduinoOTA
    .setHostname("odrive")
    .onStart([]() {})
    .onEnd([]() {})
    .onProgress([](unsigned int progress, unsigned int total) {})
    .onError([](ota_error_t error) {});
    ArduinoOTA.begin();
  /********************************************************/  
  nh.initNode();
  nh.subscribe(sub);
  delay(10);

  pinMode(LED_BUILTIN, OUTPUT); //pin number defined
  odrive.odrive_reboot(); // reboot
  for(int motor=0; motor< num_motor; motor++){
     odrive.odrive_init(motor,true,15.0); //
     delay(1000);
  }
  nh.initNode();
  nh.subscribe(sub);
  delay(10);
}

void loop() {
  ArduinoOTA.handle(); //network_config
  nh.spinOnce();
  delay(1);    

  /******************LED **********************************/
//  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
//  delay(100);                       // wait for a second
//  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
//  delay(100);  
  /*********************************************************/
    }

void joint_cb(const sensor_msgs::JointState& cmd_msg){
  joint1_angle=RadToRev(cmd_msg.position[0]);
  joint2_angle=RadToRev(cmd_msg.position[1]);
  odrive.SetPosition(1, joint1_angle);
  odrive.SetPosition(0, joint2_angle);

}

double RadToRev(float position_radians){
  return ((position_radians*reducer_rate)/(2*pi));
}
