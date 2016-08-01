#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <tf/transform_broadcaster.h>
#include <tf/transform_datatypes.h>
#include <std_srvs/Empty.h>
#include <string>

const std::string ELIKOS_ARENA_ORIGIN = "elikos_arena_origin";
const std::string ELIKOS_LOCAL_ORIGIN = "elikos_local_origin";
const std::string ELIKOS_FCU = "elikos_fcu";

bool isInit_ = false;
bool initialize(std_srvs::Empty::Request  &req,
         std_srvs::Empty::Response &res)
    {
      isInit_ = true;
      return true;
    }

int main(int argc, char* argv[])
{
  ros::init( argc, argv, "elikos_origin_init" );

  ros::NodeHandle n;

  tf::TransformListener tf_listener_;
  tf::TransformBroadcaster tf_broadcaster_;
  tf::StampedTransform originTransform;
  bool lookupDone = false;

  ros::ServiceServer service = n.advertiseService("elikos_origin_init", initialize);

  ros::Rate r(10);
  while(ros::ok())
  {
    if(isInit_)
    {
      if(!lookupDone)
      {
        try {
    			tf_listener_.lookupTransform(ELIKOS_LOCAL_ORIGIN, ELIKOS_FCU, ros::Time(0), originTransform);
          lookupDone = true;
    		}
    		catch (tf::TransformException &ex) {
    			ROS_ERROR("Origin init failed!!!! Exception : %s",ex.what());
    		}
      }
      tf_broadcaster_.sendTransform(tf::StampedTransform(originTransform.inverse(), ros::Time::now(), ELIKOS_ARENA_ORIGIN, ELIKOS_LOCAL_ORIGIN));
    }
    else
    {
      tf_broadcaster_.sendTransform(tf::StampedTransform(tf::Transform::getIdentity(), ros::Time::now(), ELIKOS_ARENA_ORIGIN, ELIKOS_LOCAL_ORIGIN));
    }
    ros::spinOnce();
    r.sleep();
  }

  return 0;
}
