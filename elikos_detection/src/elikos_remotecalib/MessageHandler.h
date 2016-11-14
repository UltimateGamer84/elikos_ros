#ifndef MESSAGE_HANDLER_REMOTECALIB
#define MESSAGE_HANDLER_REMOTECALIB
#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include "gui/headers/CalibrationWindow.hpp"
#include "gui/headers/ControlWindow.hpp"

class MessageHandler
{
public:
    MessageHandler(CalibrationWindow& calibWindow, ControlWindow& controlWindow);
    ~MessageHandler();
    void dispatchMessage(const sensor_msgs::ImageConstPtr &input);
    void dispatchDebugImage(const sensor_msgs::ImageConstPtr &input);
    void saveCalibration();

private:
    ros::NodeHandle nh_;
    image_transport::ImageTransport imgTransport_;

    image_transport::Subscriber imgSubscriber_;
    image_transport::Subscriber debugimgSubscriber_;
    
    ros::Publisher pub_;
    
    CalibrationWindow& calibWindow_;
    ControlWindow& controlWindow_;

    image_transport::Publisher pubImages_;//debug only
};

#endif /// MESSAGE_HANDLER_REMOTECALIB
