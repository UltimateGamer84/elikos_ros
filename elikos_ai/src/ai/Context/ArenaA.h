//
// Created by olivier on 01/07/16.
//

#ifndef AI_ARENA_A_H
#define AI_ARENA_A_H

#include "AbstractArena.h"

namespace ai
{

class TargetRobot;
class Configuration;

class ArenaA : public AbstractArena
{
public:
    ArenaA(Configuration* config);
    virtual ~ArenaA();

    virtual void evaluateTargetOrientation(TargetRobot& target);
    virtual int getNRotationsForOptimalDirection(const TargetRobot& target) const;

    virtual TargetRobot* findClosestTargetToGoodLine();

private:
    ArenaA();
};

}

#endif // AI_ARENA_A_H
