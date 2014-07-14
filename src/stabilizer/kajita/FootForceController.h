#ifndef __FOOT_FORCE_CONTROLLER_H__
#define __FOOT_FORCE_CONTROLLER_H__

#include <VirtualRobot/MathTools.h>
#include <Eigen/Dense>

#include <boost/assert.hpp>

#include "DampeningController.h"

/**
 * Controlls the force difference in booth feet using the rotation of the pelvis link.
 */
class FootForceController
{
public:
    FootForceController(double hipJointDistance)
    : hipJointDistance(hipJointDistance)
    , zCtrlDC(DampeningController {1000.0, 10.0, 0.0})
    {
        BOOST_ASSERT(hipJointDistance > 0);
    }

    Eigen::Matrix4f correctPelvisOrientation(const Eigen::Matrix4f& orientationRef,
                                             const Eigen::Vector3f& leftFootForceRef,
                                             const Eigen::Vector3f& rightFootForceRef,
                                             const Eigen::Vector3f& leftFootForce,
                                             const Eigen::Vector3f& rightFootForce)
    {
        zCtrlDC.update((leftFootForceRef.z() - rightFootForceRef.z()) - (leftFootForce.z() - rightFootForce.z()));

        Eigen::Matrix4f correctionMatrix = Eigen::Matrix4f::Zero();
        VirtualRobot::MathTools::rpy2eigen4f(zCtrlDC.delta / hipJointDistance, 0, 0, correctionMatrix);
        return orientationRef * correctionMatrix;
    }

private:
    double hipJointDistance;
    DampeningController zCtrlDC;
};

#endif
