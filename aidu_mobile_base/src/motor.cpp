#include <ros/ros.h>
#include <aidu_mobile_base/motor.h>
#include <threemxl/C3mxlROS.h>
#include <XMLConfiguration.h>
#include <string>

using namespace aidu;

mobile_base::Motor::Motor(std::string name, std::string motor_port_name, std::string motor_config_name, double radiusWheel) {
    
    // Load motor configuration
    CXMLConfiguration motor_config_xml;
    motor_config_xml.loadFile(motor_config_name);
    
    // ThreeMXL initialization
    // Create configuration
    config = new CDxlConfig();
    config->readConfig(motor_config_xml.root().section(name.c_str()));
    this->name = name;
    this->radiusWheel = radiusWheel;

    // Create and configure 3mxl motor
    motor = new C3mxlROS(motor_port_name.c_str());
    motor->setConfig(config);
    int init=-20;
    while (init != 0 && ros::ok()){
      init=motor->init();
      sleep(1);
      //ROS_INFO("init: %d",init);
    }
    
    motor->setWheelDiameter(radiusWheel * 2.0);
    motor->set3MxlMode(POSITION_MODE);
    motor->setLinearAcceleration(0.5);
    currentVelocity = 0;

}

void mobile_base::Motor::setVelocity(float velocity) {
   
    if (fabs(velocity-currentVelocity) > 0.005 || velocity==0.0) {
        
        
        // Send velocity to the 3mxl board
        ROS_INFO("%s: Setting velocity to %f", name.c_str(), velocity);
        
        // Check mode of 3mxl
        motor->get3MxlMode();
        if(motor->present3MxlMode() != SPEED_MODE){
        motor->set3MxlMode(SPEED_MODE);
        }
        
        // Send speed to 3mxl
        motor->setSpeed(velocity);
    } else {
      ROS_INFO("velocity treshold target:%f   current:%f",velocity,currentVelocity);
    }
}

void mobile_base::Motor::setPosition(float position) {

    // Send velocity to the 3mxl board
    ROS_INFO("%s: Setting position+initial to %f", name.c_str(), position+initialPos);
    
    // Check mode of 3mxl
    motor->get3MxlMode();
    if(motor->present3MxlMode() != POSITION_MODE){
        motor->set3MxlMode(POSITION_MODE);
    }
    
    ROS_INFO("%s: Present position: %f", name.c_str(), motor->presentLinearPos());
    
    // Send position to 3mxl
    motor->setLinearPos(position+initialPos,0.2);
}

void mobile_base::Motor::reset() {
    update();
    initialPos = motor->presentLinearPos();
}

void mobile_base::Motor::update() {
    motor->getPosAndSpeed();
    motor->getLinearPos();
    //motor->getStatus();
    currentVelocity=motor->presentSpeed();
    //ROS_INFO("%s status: 0x%X", name.c_str(), motor->presentStatus());
}

double mobile_base::Motor::getLinearVelocity() {
    return motor->presentSpeed() * radiusWheel;
}

double mobile_base::Motor::getLinearPosition() {
    return motor->presentLinearPos() - initialPos;
}

mobile_base::Motor::~Motor(){
    motor->setSpeed(0);
    serial_port->port_close();
    delete config;
    delete motor;
    delete serial_port;
}
