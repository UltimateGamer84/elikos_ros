#include <thread>

#include <iostream>

#include "MessageEmulator.h"
#include "MessageHandler.h"

namespace emu
{

const std::string MessageEmulator::SIM_MAV_FRAME = "MAV";
const std::string MessageEmulator::SIM_TRGT_FRAME = "trgtRobot";

MessageEmulator* MessageEmulator::instance_ = nullptr;

MessageEmulator::MessageEmulator()
{
    trgtPub_ = nh_.advertise<elikos_ros::TargetRobotArray>(ai::TRGT_TOPIC, 1);
}

MessageEmulator* MessageEmulator::getInstance()
{
   if (instance_ == nullptr)
   {
       instance_ = new MessageEmulator();
   }
   return instance_;
}

void MessageEmulator::freeInstance()
{
    delete instance_;
    instance_ = nullptr;
}

void MessageEmulator::lookForTf()
{
    ros::Rate rate(30);
    while(ros::ok())
    {
        lookForTargets();
        lookForMav();
        ros::spinOnce();
        rate.sleep();
    }
}

void MessageEmulator::lookForMav()
{
    tf::StampedTransform stf;
    try
    {
        listener_.lookupTransform(ai::WORLD_FRAME, SIM_MAV_FRAME, ros::Time(0), stf);
    }
    catch (tf::TransformException e)
    {
        return;
    }

    mavPosition_ = stf.getOrigin();
    broadcaster_.sendTransform(tf::StampedTransform(stf, ros::Time::now(), ai::WORLD_FRAME, ai::MAV_FRAME));
}


void MessageEmulator::lookForTargets()
{
    targets_.targets.clear();
    assert(targets_.targets.size() == 0);
    for (int i = 0; i < N_TRGT; ++i)
    {
        tf::StampedTransform stf;
        try
        {
            listener_.lookupTransform(ai::WORLD_FRAME, SIM_TRGT_FRAME + std::to_string(i), ros::Time(0), stf);
            addTarget(stf, i);
        }
        catch(tf::TransformException e)
        {
            continue;
        }
    }
    trgtPub_.publish(targets_);
}

void MessageEmulator::addTarget(const tf::StampedTransform& stf, unsigned char id)
{
    tf::Pose poseTf(stf);
    geometry_msgs::Pose poseMsg;
    tf::poseTFToMsg(poseTf, poseMsg);

    elikos_ros::TargetRobot target;
    target.color = 0;
    target.id = id;
    target.poseOrigin.pose = poseMsg;
    targets_.targets.push_back(target);
}
    
};