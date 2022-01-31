///*
// * E Stop Publisher
// * Author: Muhammad Suleman, Maxwell Nguyen, Roshan Cheriyan, Malachai Smith
// * Author for led Maxwell Nguyen

#include <ros.h>

#include <std_msgs/Bool.h>

void CheckAutonomousCallback(const std_msgs::Bool & vehicle_engage_msg);

//All of the ROS definitions
ros::NodeHandle nh; //Handles the various nodes
std_msgs::Bool bool_msg;

//Initialize the ROS node, the subscribing node, and the publishing node
ros::Publisher estop_pub("gem_estop", & bool_msg);

//The node we are subscribing to for the autonomous light to either be on or off
ros::Subscriber < std_msgs::Bool > vehicle_engage("vehicle/engage", & CheckAutonomousCallback);

//Defines the arduino pins
//int inputPin = A4;  //Input Voltage (A4)
int lightPin = 9; //Output Signal (D4)
int estop1 = 2; //E-Stop Pin (D2)
int estop2 = 3; //E-Stop Pin (D3)
int estop3 = 4; //E-Stop Pin (D4) -- SEE WHAT PINS ARE AVAILABLE. COULD DAISY CHAIN THE ESTOPS TOGETHER TO ONE PIN
int estop4 = 5; //E-Stop Pin (D5)
bool flag = false;

void CheckAutonomousCallback(const std_msgs::Bool & vehicle_engage_msg) {
   flag = vehicle_engage_msg.data;
}

void setup() {
  nh.initNode();
  pinMode(lightPin, OUTPUT);
  pinMode(estop1, INPUT);
  pinMode(estop2, INPUT);
  pinMode(estop3, INPUT);
  pinMode(estop4, INPUT);

  nh.advertise(estop_pub);
  nh.subscribe(vehicle_engage);
}

//Main loop that the program runs
void loop() {
  // Makes the light in stead state
  digitalWrite(lightPin, HIGH);
  if (flag) {
    delay(250);
    digitalWrite(lightPin, LOW);
    delay(250);
    flag = false;
  }

  // Checks for estop button press event
  if ((estop1 || estop2 || estop3 || estop4) == LOW) {
    bool_msg.data = true;
  } else {
    bool_msg.data = false;
  }
  estop_pub.publish( & bool_msg);
  nh.spinOnce();
}
