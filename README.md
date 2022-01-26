# IGVC Emergency Stop Arduino  
 This arduino code allows functionality of E-stop buttons. In a button press for E-Stop pins 2-5, it will publish a new node that causes a vehicle's velocity to return to 0. Separately, it subscribes to the `vehicle_engaged` node to callback if it is in an autonomous state to blink pin 13.  


## Requires  

Following are the requirements for the package.  
- arduino
- ROS Serial
- ROS Melodic
- https://github.com/msuleman67h/igvc_estop/
