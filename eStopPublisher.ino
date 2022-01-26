///*
// * E Stop Publisher
// * Author: Muhammad Suleman, Maxwell Nguyen, Roshan Cheriyan, Malachai Smith
// * Author for led Maxwell Nguyen

#include <ros.h>
#include <std_msgs/Bool.h>
//#include <std_msgs/UInt16.h>

void CheckAutonomousCallback(const std_msgs::Bool& toggle_msg);

//All of the ROS definitions
ros::NodeHandle  nh; //Handles the various nodes
std_msgs::Bool bool_msg;


//The node we are subscribing to for the autonomous light to either be on or off

//Initialize the ROS node, the subscribing node, and the publishing node
ros::Publisher estop_pub("gem_estop",&bool_msg);
// ros::Subscriber<std_msgs::UInt16> sub("pure_pursuit", 1000, purePursuitCallback);
ros::Subscriber<std_msgs::Bool> vehicle_engaged("vehicle/engaged", CheckAutonomousCallback);

//Defines the arduino pins
//int inputPin = A4;  //Input Voltage (A4)
int lightPin = 13;  //Output Signal (D4)
int estop1 = 2; //E-Stop Pin (D2)
int estop2 = 3; //E-Stop Pin (D3)
int estop3 = 4; //E-Stop Pin (D4) -- SEE WHAT PINS ARE AVAILABLE. COULD DAISY CHAIN THE ESTOPS TOGETHER TO ONE PIN
int estop4 = 5; //E-Stop Pin (D5)




void CheckAutonomousCallback(const std_msgs::Bool& toggle_msg){
    if(toggle_msg.data){
        blink(); //Blink the safety light
    }
    else{
        digitalWrite(lightPin, LOW); //Turn the safety light off
    }
}


void setup(){  
    nh.initNode();
    pinMode(lightPin, OUTPUT);
    pinMode(estop1, INPUT);
    pinMode(estop2, INPUT);
    pinMode(estop3, INPUT);
    pinMode(estop4, INPUT);
    //Serial.begin(9600); If we need any printing materials



    nh.advertise(estop_pub);
    nh.subscribe(vehicle_engaged);
}

//Main loop that the program runs
void loop(){
    if((estop1 or estop2 or estop3 or estop4) == HIGH){
        // bool_msg.data = true;
        estop_pub.publish( &bool_msg );
        nh.spinOnce();
        delay(100);
    } 

    nh.spinOnce();
}

void blink(){
  digitalWrite(lightPin, HIGH);
  delay(500);
  digitalWrite(lightPin, LOW);
  delay(500);
}
