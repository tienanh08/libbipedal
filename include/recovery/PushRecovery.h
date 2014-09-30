#ifndef __PUSH_RECOVERY_H__
#define __PUSH_RECOVERY_H__

#include "../bipedal.h"

#include <Eigen/Dense>

#include <VirtualRobot/VirtualRobot.h>

namespace Bipedal
{

/**
 * This class is an interface to push recovery mechanism.
 */
class PushRecovery
{
public:
    /**
     * dt is the time in seconds since the last call to this function
     * Needs to be called in each iteration of the control loop before
     * the call to isFalling.
     */
    virtual void update(double dt) = 0;

    /**
     * Returns true if it was detected that we are falling.
     */
    virtual bool isFalling() const = 0;

    // For debugging
    virtual const VirtualRobot::MathTools::ConvexHull2DPtr getLeftSupportPolygone() const = 0;
    virtual const VirtualRobot::MathTools::ConvexHull2DPtr getRightSupportPolygone() const = 0;
    virtual const VirtualRobot::MathTools::ConvexHull2DPtr getDualSupportPolygone() const = 0;

    virtual const Eigen::Matrix4f& getLeftFootPose() const = 0;
    virtual const Eigen::Matrix4f& getRightFootPose() const = 0;
    virtual const Eigen::Matrix4f& getChestPose() const = 0;
    virtual const Eigen::Matrix4f& getPelvisPose() const = 0;
    virtual Bipedal::SupportPhase getSupportPhase() const = 0;
};

}

#endif
