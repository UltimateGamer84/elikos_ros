//
// Created by olivier on 01/07/16.
//

#ifndef AI_WHITE_LINE_H
#define AI_WHITE_LINE_H

#include "AbstractLine.h"

namespace ai
{

class WhiteLine : public AbstractLine
{
public:
    WhiteLine(const tf::Point& cornerA, const tf::Point& cornerB);
    virtual ~WhiteLine();

    virtual void evaluate(const TargetRobot& robot, TargetOrientationEvaluation& evaluation);

private:
    WhiteLine() = delete;
};

}

#endif // AI_WHITELINE_H
