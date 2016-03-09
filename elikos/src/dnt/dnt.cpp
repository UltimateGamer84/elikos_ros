#include <memory>
#include <ros/ros.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>

#include "MessageHandler.h"

int main(int argc, char* argv[])
{
    // ROS Init
    ros::init( argc, argv, "elikos_dnt" );
   
    MessageHandler messageHandler;

    ros::Rate r(30);
    // Endless loop
    while(ros::ok()) 
    {
        ros::spinOnce();
        r.sleep();
    }
}