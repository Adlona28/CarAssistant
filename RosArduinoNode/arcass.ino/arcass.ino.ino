//ROS
#include <ros.h>
#include <std_srvs/SetBool.h>
#include <std_msgs/String.h>
//LCD
#include <LiquidCrystal.h>

/* LCD initalization */
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

/* ROS stuff initialization */
ros::NodeHandle nh;

bool large_lights = false;
bool short_lights = false;

void onShortLightsCallback (const std_srvs::SetBool::Request &req, std_srvs::SetBool::Response &res) { 
  if (not short_lights and not large_lights) {digitalWrite(9, HIGH); res.success = true; short_lights = true; res.message = "Shorts on!";}
  else {
    if (large_lights) res.message = "Shut large first"; 
    else res.message = "Shorts are on!"; 
    res.success = false; 
  }
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print(res.message);
}

void offShortLightsCallback (const std_srvs::SetBool::Request &req, std_srvs::SetBool::Response &res) {
  if (short_lights) {digitalWrite(9, LOW); res.success = true; short_lights = false; res.message = "Short off!";}
  else {
    res.success = false;
    res.message = "Short are off!";
  }
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print(res.message);
}

void onLargeLightsCallback (const std_srvs::SetBool::Request &req, std_srvs::SetBool::Response &res) {
  if (not large_lights and not short_lights) {digitalWrite(8, HIGH); res.success = true; large_lights = true; res.message = "Large on!";}
  else {
    if (short_lights) res.message = "Shut short first"; 
    else res.message = "Large are on!"; 
    res.success = false;
  }
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print(res.message);
}

void offLargeLightsCallback (const std_srvs::SetBool::Request &req, std_srvs::SetBool::Response &res) {
  if (large_lights) {digitalWrite(8, LOW); res.success = true; large_lights = false; res.message = "Large off!";}
  else {
    res.success = false;
    res.message = "Large are off!";
  }
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print(res.message);
}

ros::ServiceServer<std_srvs::SetBool::Request, std_srvs::SetBool::Response> on_short_Lights_service ("on_short_lights",   &onShortLightsCallback); 
ros::ServiceServer<std_srvs::SetBool::Request, std_srvs::SetBool::Response> off_short_Lights_service("off_short_lights", &offShortLightsCallback); 
ros::ServiceServer<std_srvs::SetBool::Request, std_srvs::SetBool::Response> on_large_Lights_service ("on_large_lights",   &onLargeLightsCallback);
ros::ServiceServer<std_srvs::SetBool::Request, std_srvs::SetBool::Response> off_large_Lights_service("off_large_lights", &offLargeLightsCallback); 

/* Topic Subscriber & Callbacks */

void toPrintCallback (const std_msgs::String &msg) {
    lcd.begin(16, 2);
    lcd.setCursor(0, 1);
    lcd.print(msg.data);
}

ros::Subscriber<std_msgs::String> toPrint_subscriber ("/assistant_dealer/assistant_dealer/command_to_print", &toPrintCallback);

void setup() {
  nh.initNode();
  nh.advertiseService(on_short_Lights_service);
  nh.advertiseService(off_short_Lights_service);
  nh.advertiseService(on_large_Lights_service);
  nh.advertiseService(off_large_Lights_service);
  nh.subscribe(toPrint_subscriber); 
  //lcd init rows and cols
  lcd.begin(16, 2);
  lcd.setCursor(0, 1);
  digitalWrite(8, LOW); //First set low state...
  digitalWrite(9, LOW);
}

void loop() {
  nh.spinOnce();
  delay(2);
}

