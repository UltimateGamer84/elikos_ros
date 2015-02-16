/*
 * defines.cpp
 *
 *  Created on: Jan 15, 2015
 *      Author: Myriam Claveau-Mallet
 *      Brief: This file contains all topics definitions and functions to create publishers
 *             for these topics, and other static or const variables and enum. Also are
 *             included commun includes and pre-compiler defines.
 */


#ifndef _DEFINES_CPP_
#define _DEFINES_CPP_


/* *************************************************************************************************
 * ***           INCLUDES
 * *************************************************************************************************
 */


#include <ros/ros.h>
#include <vector>
#include <string>


/* *************************************************************************************************
 * ***           DEFINES
 * *************************************************************************************************
 */

#ifndef PI
#define PI 3.14159265
#endif


/* *************************************************************************************************
 * ***           ENUMS
 * *************************************************************************************************
 */


/*
 * VERY IMPORTANT NOTE REGARDING TOPICS
 *
 * For every new topic included in the following lists, one should ABSOLUTLY
 *
 *     (1) include new topic in the enum,
 *     (2) include new topic string in the std::vector TOPICS_NAMES,
 *     (3) make sure both enum and vector entry have the SAME POSITION.
 *
 * This is because each enum value represents an index in TOPICS_NAMES vector.
 */

///
/// Define topics to avoid confusion in topics denomination
///
enum topics
{
    robotsPos = 0,
    robotsim_robot_markers,
    robotsim_mav_marker,
    robotsim_setpoint_marker,
    robotsim_arena_marker,
    mavros_setpoint_local_position,
    mavros_localPosition_local, // quad position
    mavros_imu_data, // quad orientation
    NB_TOPICS
};


///
/// Define robots possible types. Will be used to identify robots types
/// in the message RobotPos.
///
enum robotTypes
{
	groundRobot = 0,
	obstacleRobot,
	quadRobot,
	unknow
};


/* *************************************************************************************************
 * ***           STATIC VARIABLES
 * *************************************************************************************************
 */

///
/// Provide access to enum names
///
const std::string arr[] = // TOPICS_NAMES
{
	"robotDetect/robotsPos", // robotDetec topic : communicate the located robots positions
	"robotsim/robot_markers",
	"robotsim/mav_marker",
	"robotsim/setpoint_marker",
	"robotsim/arena_marker",
	"mavros/setpoint/local_position", // quad : set position
	"mavros/localPosition/local", // quad position
	"mavros/imu/data" // quad orientation
};
static const std::vector<std::string> TOPICS_NAMES
(
    arr, arr + sizeof(arr) / sizeof(arr[0])
);


#endif // _DEFINES_CPP_
