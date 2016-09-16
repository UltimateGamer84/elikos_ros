/**
* @file		ai/internalModel/TargetRobot.hpp
* @author	Myriam Claveau-Mallet
* @date		02/08/2015
*/

#ifndef AI_TARGET_ROBOT_HPP
#define AI_TARGET_ROBOT_HPP

#include "Robot.hpp"

namespace elikos_ai {

/**
 * @class	elikos_ai::TargetRobot	TargetRobot.hpp	"Definition"
 * @brief	class for TargetRobot in the ai's internal model
 */

class TargetRobot : public Robot
{
public:

    virtual ~TargetRobot() {}
	TargetRobot( int id, tf::Point relativePosition, float orientation ); //constructor
    TargetRobot( int id, tf::Point relativePosition, float orientation, tf::Vector3 speed ); //constructor

	Color getColor () { return this->color; }


private:

	Color color;


    /* *************************************************************************************************
     * ***           HIDDEN CONSTRUCTORS (do not implement)
     * *************************************************************************************************
     */

    TargetRobot();
	TargetRobot& operator= (const TargetRobot&);
	TargetRobot (const TargetRobot&);

}; // class elikos_ai::TargetRobot

} // namespace elikos_ai

#endif // AI_TARGET_ROBOT_HPP