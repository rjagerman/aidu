#ifndef AIDU_ELEVATOR__ACTIONS__MOVEINELEVATOR_H
#define AIDU_ELEVATOR__ACTIONS__MOVEINELEVATOR_H

#include <ros/ros.h>
#include <aidu_elevator/actions/action.h>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Twist.h>
#include <aidu_vision/DistanceSensors.h>

namespace aidu {
    namespace elevator {
        class MoveInElevator : public aidu::elevator::Action {
            public:
            
		MoveInElevator(ros::NodeHandle* nh);
		~MoveInElevator();
                void execute();
                bool finished();
                
		void laserscancallback(const sensor_msgs::LaserScan::ConstPtr& scan_msg);
		void sensorcallback(const aidu_vision::DistanceSensors::ConstPtr& dist_msg);
		void controlloop(double target_dist, double target_angle);
		void SetPos(double x, double angle);
                
            protected:                
		ros::Publisher basepositionPublisher, speedPublisher;
		ros::Subscriber laserscanSubsciber, sensor_sub;
		int rotationdirection;
		double front_left, front_right, dist_arm, distance;
		bool begining,action_finished;
        
        };
    }
}

#endif