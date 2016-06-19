#ifndef AI_TRANSLATOR
#define AI_TRANSLATOR

#include <string>
#include <ros/ros.h>
#include <tf/transform_listener.h>

#include <elikos_ros/TargetRobot.h>
#include <elikos_ros/TargetRobotArray.h>
#include <tf/transform_broadcaster.h>

namespace tf
{
    class Vector3;
}

namespace ai
{

class Agent;

class MessageHandler
{
public:
    static const std::string DNT_TOPIC;
    static const std::string MAV_TOPIC;
    static const std::string MAV_FRAME;
    static const std::string WORLD_FRAME;

    static MessageHandler* getInstance();
    static void freeInstance();

    void lookForMessages();
    void sendDestination(const tf::Vector3& destination);

private:
    static MessageHandler* instance_;

    ros::NodeHandle nh_;
    ros::Subscriber sub_;
    ros::Publisher mavPublisher_;
    tf::TransformBroadcaster br_;

    Agent* agent_{ nullptr };

    void handleMessage(const elikos_ros::TargetRobotArray::ConstPtr& input);

    MessageHandler();
    ~MessageHandler() = default;
};

}

#endif /// MESSAGE_HANDLER