
/*******************ros******************************/
#include <ros.h>
#include <std_msgs/String.h>
/********************network_config*********************/
#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
const char* ssid = "ohaginia";
const char* password = "Shoma0218";
IPAddress server(192, 168, 2, 4); //ip adress(sh command "ip a")
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
      for (int i = 0; i < length; i++)
        client.write(data[i]);
    }
    unsigned long time() {
      return millis();
    }
};
/**************************************************************/
#define LED_BUILTIN 15 //debug led

ros::NodeHandle_<WiFiHardware>  nh; //declared nodehandle
std_msgs::String str_msg;
ros::Publisher chatter("chatter", &str_msg);
char hello[13] = "hello world!";

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
  .onStart([]() {})
  .onEnd([]() {})
  .onProgress([](unsigned int progress, unsigned int total) {})
  .onError([](ota_error_t error) {});
  ArduinoOTA.begin();

  /********************************************************/
  nh.initNode();
  nh.advertise(chatter);
  delay(10);

  pinMode(LED_BUILTIN, OUTPUT); //pin number defined
}

void loop() {
  ArduinoOTA.handle(); //network_config
  /******************LED **********************************/
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(100);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(100);
  /*********************************************************/
  str_msg.data = hello;
  chatter.publish( &str_msg );
  nh.spinOnce();
  delay(1000);
}
