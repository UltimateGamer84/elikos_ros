#include "CmdTopInteraction.h"

CmdTopInteraction::CmdTopInteraction(ros::NodeHandle* nh, int id)
    : CmdAbs(nh, id)  
{
    targetPosition_.setData(tf::Transform(tf::Quaternion{ 0.0, 0.0, 0.0, 1.0 }, tf::Vector3{ 0.0, 0.0, 2.0 }));
    targetPosition_.child_frame_id_ = MAV_FRAME;
    targetPosition_.frame_id_ = WORLD_FRAME;
}

CmdTopInteraction::~CmdTopInteraction()
{
    int i = 0;
}

void CmdTopInteraction::execute()
{
    interactionStatus_ = InteractionState::LANDING;
    ros::Rate rate(30.0);

    tf::Vector3 groundPosition = targetPosition_.getOrigin();
    groundPosition.setZ(HIGH_OF_ROBOT);
    groundPosition.setY(cmdDestination_.getY());
    groundPosition.setX(cmdDestination_.getX());
    targetPosition_.setOrigin(groundPosition);

    
    while (interactionStatus_ != InteractionState::DONE)
    {
        ros::spinOnce();
        try 
        {
            tf_listener_.lookupTransform(WORLD_FRAME, MAV_FRAME, ros::Time(0), lastPosition_);
        }

        catch (tf::TransformException e)
        {
            ROS_ERROR("%s",e.what());
        }

        double distance = lastPosition_.getOrigin().distance(targetPosition_.getOrigin());
        if (distance > THRESHOLD)
        {
            targetPosition_.stamp_ = ros::Time::now();
            tf_broadcaster_.sendTransform(targetPosition_);
            rate.sleep();
        }
        
        else 
        {
            if(interactionStatus_ == InteractionState::HAS_TOUCHED_ROBOT)
            {
                interactionStatus_ = InteractionState::DONE;
            }
            else
            {
                interactionStatus_ = InteractionState::HAS_TOUCHED_ROBOT;
                tf::Vector3 securityPosition = targetPosition_.getOrigin();
                securityPosition.setZ( 1.0 );
                targetPosition_.setOrigin(securityPosition);
            }
        }
    }
}

void CmdTopInteraction::abort()
{
}

void CmdTopInteraction::ajustement() //Paramètre à recevoir : XY du robot au sol
{
    //TODO : Faire l'update de la position du robot
}
