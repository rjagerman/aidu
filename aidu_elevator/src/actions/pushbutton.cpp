#include <ros/ros.h>
#include <aidu_elevator/actions/pushbutton.h>
#include <aidu_elevator/Button.h>
#include <aidu_robotarm/robot_arm_positions.h>
#include <tf/transform_listener.h>
#include <sensor_msgs/JointState.h>
#include <math.h>

using namespace aidu::elevator;

PushButton::PushButton(ros::NodeHandle* nh) : Action::Action(nh) {
  
    //subscriber
    buttonSubscriber = nh->subscribe<aidu_elevator::Button>("/elevator/button/classified", 1, &PushButton::visibleButton, this);
    sensor_sub = nh->subscribe("/sensors", 1, &PushButton::sensorcallback, this);
    jointState_sub = nh->subscribe("/arm_state", 1, &PushButton::arm_statecallback, this);
    //publisher
    robot_arm_positions_pub= nh->advertise<aidu_robotarm::robot_arm_positions>("/robot_arm_positions",1);
    
    //initialising variables
    this->buttonPushed = false;
    arm_x=arm_y=arm_z=0.0;
    front_left=front_right=0.0;
    horizontal_fov=1.07115918; //field of view of the webcam in radians 
    vertical_fov=0.644356361;
      
}

PushButton::~PushButton() {
    
}

void PushButton::execute() {
      //ROS_INFO("Executing push button action");
      aidu_robotarm::robot_arm_positions positions;
      positions.translation=positions.extention=positions.rotation=0.0;
      double arm_length=0.15;
      //getting position of the webcam
      try{
	 listener.lookupTransform("base_link", "webcam_link", ros::Time(0), transform);
      }
      catch (tf::TransformException ex){
	//ROS_ERROR("%s",ex.what());
      }      
      arm_x=transform.getOrigin().x();
      arm_y=transform.getOrigin().y();
      arm_z=transform.getOrigin().z();
      //ROS_INFO("x:%f y:%f z:%f",x,y,z);
      
      //getting distance
      double dist_z=front_left;
      
      // get position of button
      double but_x=convert(horizontal_fov,img_x,dist_z,1280);
      double but_y=convert(vertical_fov,img_y,dist_z,720);
      //ROS_INFO("button positions: x:%f   y:%f",but_x ,but_y);
      
      //adjusting vertical position
      if (fabs(but_y) > 0.01){
	positions.translation=but_y+translation;
      }
      if (fabs(but_x)>0.01){
	positions.rotation=rotation+atan(but_x/(dist_z+arm_length));
      }
      
}

bool PushButton::finished() {
    return this->buttonPushed;
}

void PushButton::visibleButton(const aidu_elevator::Button::ConstPtr& message) {
  img_x=message->x;
  img_y=message->y;
  
}

void PushButton::sensorcallback(const aidu_vision::DistanceSensors::ConstPtr& dist_msg){
 front_left=dist_msg->Frontleft; 
 front_right=dist_msg->Frontright;
}

void PushButton::arm_statecallback(const sensor_msgs::JointState::ConstPtr& joint_msg){
  translation=joint_msg->position[0];
  rotation=joint_msg->position[1];
  extension=joint_msg->position[2];
  
}
       
double PushButton::convert(double fov, double img_x,double z,double resolution){
  double theta=-fov/2.0+(fov*img_x/resolution);
  double x=tan(theta)*z;
  return(x);
}