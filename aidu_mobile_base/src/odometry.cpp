
#include <aidu_mobile_base/odometry.h>
#include <aidu_mobile_base/BaseState.h>
#include <nav_msgs/Odometry.h>
#include <math.h>
#include <algorithm>
#include <deque>

using namespace aidu;

mobile_base::Odometry::Odometry(){
    stateSubscriber = nh->subscribe("/base/state", 5, &mobile_base::Odometry::processState, this);
    odometryPublisher = nh->advertise<nav_msgs::Odometry>("/odom", 1);
}

mobile_base::Odometry::~Odometry() {
    
}

/*template <typename T>
double mean(T begin, T end)
{
    double sum=0, count=0;
    while(begin!=end)
    {
        sum+=*begin++;
        count++;
    }

    return sum/count;
}
std::deque<double> errors;

    double speed = dth / dt;
    if(speeds.size() >= 30) {
        speeds.pop_front();
    }
    speeds.push_back(speed);
    double calculated = mean(speeds.begin(), speeds.end());

    double error = calculated - vtheta;
    errors.push_back(error);
    if(errors.size() >= 30*3) {
        errors.pop_front();
    }
    error = mean(errors.begin(), errors.end());
    ROS_INFO("Calculated: %f --- Reported: %f --- Error: %f", calculated, vtheta, error);
    
*/

void mobile_base::Odometry::processState(const aidu_mobile_base::BaseState::ConstPtr& msg) {
    
    ros::Time currentTime = ros::Time::now();
    previousTime = currentTime;
    
    double dLeftWheel = msg->left.position - previousLeftWheelPosition;
    double dRightWheel = msg->right.position - previousRightWheelPosition;
    
    double r = (dLeftWheel + dRightWheel) / 2.0;
    
    theta = msg->angle.position;
    double dx = cos(theta) * r;
    double dy = sin(theta) * r;
    
    double v = (msg->left.speed + msg->right.speed) / 2.0;
    v = (1.0 + 0.071409) * v;
    double vx = cos(theta) * v;
    double vy = sin(theta) * v;
    double vtheta = msg->angle.speed;
    
    x += dx;
    y += dy;
    
    //since all odometry is 6DOF we'll need a quaternion created from yaw
    geometry_msgs::Quaternion odom_quat = tf::createQuaternionMsgFromYaw(theta);

    //first, we'll publish the transform over tf
    geometry_msgs::TransformStamped odom_trans;
    odom_trans.header.stamp = currentTime;
    odom_trans.header.frame_id = "odom";
    odom_trans.child_frame_id = "base_link";

    odom_trans.transform.translation.x = x;
    odom_trans.transform.translation.y = y;
    odom_trans.transform.translation.z = 0.0;
    odom_trans.transform.rotation = odom_quat;

    //send the transform
    odometryBroadcaster.sendTransform(odom_trans);

    //next, we'll publish the odometry message over ROS
    nav_msgs::Odometry odom;
    odom.header.stamp = currentTime;
    odom.header.frame_id = "odom";

    //set the position
    odom.pose.pose.position.x = x;
    odom.pose.pose.position.y = y;
    odom.pose.pose.position.z = 0.0;
    odom.pose.pose.orientation = odom_quat;

    //set the velocity
    odom.child_frame_id = "base_link";
    odom.twist.twist.linear.x = vx;
    odom.twist.twist.linear.y = vy;
    odom.twist.twist.angular.z = vtheta;

    //publish the message
    odometryPublisher.publish(odom);
    
    // Store values for next iteration
    previousLeftWheelPosition = msg->left.position;
    previousRightWheelPosition = msg->right.position;
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "odometry");
    mobile_base::Odometry odometry;
    odometry.spin();
    return 0;
}