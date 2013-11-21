#ifndef AIDU_MOBILE_BASE__BASE_H
#define AIDU_MOBILE_BASE__BASE_H

#include <ros/ros.h>
#include <aidu_core/node.h>
#include <aidu_mobile_base/motor.h>
#include <aidu_mobile_base/Pos.h>
#include <geometry_msgs/Twist.h>



namespace aidu {
  namespace mobile_base {
    
    //this structure contains the speed of the left and right motors
    struct Vel {
      float leftspeed;
      float rightspeed;
    };
    
      
    class Base : public aidu::core::Node {
    public:
      
      Base();
      ~Base();
      void speed(const geometry_msgs::Twist::ConstPtr& msg);///< sets the velocity of a motor
      void pos(const aidu_mobile_base::Pos::ConstPtr& msg);///< sets the positon of a motor
      void spin();///< reads the position of the motors
      Vel calcVelocity(float velocity,float angle); ///< calculates the speed difference between the left and right motor

    protected:

      aidu::mobile_base::Motor* leftWheelMotor;
      aidu::mobile_base::Motor* rightWheelMotor;
      ros::Subscriber possubscriber; ///< The subscriber for the position messages
      ros::Subscriber speedsubscriber; ///< The subscriber for the position messages
      ros::Publisher pospublisher; ///< The publisher for the position of the base
    };
  }
}

#endif
