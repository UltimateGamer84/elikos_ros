#ifndef AI_MOVEMENT_STATE_H
#define AI_MOVEMENT_STATE_H

#include "AbstractCommand.h"

namespace ai
{

class CommandQueue;

class MovementCommand : public AbstractCommand
{
public:
    static constexpr double FLIGHT_HEIGHT{ 2.0 };
    static constexpr double WAIT_TIME { 5.0 };

    MovementCommand(QuadRobot* quad, TargetRobot* target);
    virtual ~MovementCommand();
    virtual bool isCommmandDone();
    virtual void execute();

private:
    MovementCommand() = delete;
};

}

#endif // AI_MOVEMENT_STATE_H