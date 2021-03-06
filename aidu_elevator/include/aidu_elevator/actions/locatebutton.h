#ifndef AIDU_ELEVATOR__ACTIONS__LOCATEBUTTON_H
#define AIDU_ELEVATOR__ACTIONS__LOCATEBUTTON_H

#include <ros/ros.h>
#include <sensor_msgs/JointState.h>
#include <aidu_elevator/actions/action.h>
#include <aidu_elevator/Button.h>

namespace aidu {
    namespace elevator {
        class LocateButton : public aidu::elevator::Action {
            public:
            
                LocateButton(ros::NodeHandle* nh, int button, double angle, double translationStep);
                ~LocateButton();
                void execute();
                bool finished();
                
                void visibleButton(const aidu_elevator::Button::ConstPtr& message);
                void updateArmState(const sensor_msgs::JointState::ConstPtr& message);
                
            protected:
	      
                int button;
                bool buttonFound;
		
		bool begin;
                
                double translation;
                double rotation;
                
                double translationSpeed;
                double rotationSpeed;
                
                double wantedTranslation;
                double wantedRotation;
                
                double translationStep;
                double rotationStep;
                
                double translationEpsilon;
                double rotationEpsilon;
                
                double translationMaximum;
                double translationMinimum;
                
                double rotationMaximum;
                double rotationMinimum;
		
		ros::Time wait_start;
                
                ros::Subscriber buttonSubscriber;
                ros::Subscriber robotArmSubscriber;
		ros::Publisher robotArmPublisher;
        
        };
    }
}

#endif