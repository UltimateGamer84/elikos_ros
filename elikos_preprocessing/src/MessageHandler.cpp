//
// Created by olivier on 9/29/16.
//

#include "MessageHandler.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <tf/tf.h>

#include "PreProcessing.h"

namespace preprocessing {


MessageHandler::MessageHandler()
    : it_(nh_)
{
    imageSub_ = it_.subscribe("image_rect", 1, &MessageHandler::cameraCallback, this);
    preprocessedPub_ = it_.advertise("image_preprocessed", 1);
}

MessageHandler::~MessageHandler()
{
}

MessageHandler* MessageHandler::getInstance()
{
    static MessageHandler instance_;
    return &instance_;
}

void MessageHandler::lookForMessages()
{
    ros::spin();
}

void MessageHandler::cameraCallback(const sensor_msgs::ImageConstPtr& msg)
{
    cv::Mat input = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8)->image;
    cv::Mat output;
    cv::Mat bwOutput;
    preProcessing_.preProcessImage(input, ros::Time::now(), output, bwOutput);

    sensor_msgs::ImagePtr msgPreproc = cv_bridge::CvImage(std_msgs::Header(), "bgr8", output).toImageMsg();
    preprocessedPub_.publish(msgPreproc);
}

}