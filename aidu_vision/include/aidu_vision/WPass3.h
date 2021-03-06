#ifndef AIDU_VISION__WPASS3_H
#define AIDU_VISION__WPASS3_H

#include <ros/ros.h>
#include <aidu_core/node.h>
#include <aidu_vision/DistanceSensors.h>
#include <aidu_mobile_base/State.h>
#include <sensor_msgs/LaserScan.h>


namespace aidu {
  
  
  class LaserScanHandler : public aidu::core::Node {
  public:
    LaserScanHandler();
    void LaserScanCallback(const sensor_msgs::LaserScan::ConstPtr& scanmsg);///< handles the sensor input
    double average(double array[],int size);
  protected:
    ros::Subscriber scanmsg,statesubscriber;
    ros::Publisher speedpublisher;
    
    ros::Time angularTime;
    double targetdistance,targetangle; ///< target position of the robot
    double maxAngularSpeed,maxLinearSpeed;///< maximum speed of the robot
  };
}




#endif
