#ifndef __KAJITA_STABILIZER_H__
#define __KAJITA_STABILIZER_H__

#include "../TrajectoryController.h"

class FootForceController;
class FootTorqueController;
class ChestPostureController;
class ForceDistributor;
class ForceSensor;
class ReferenceIK;
template<typename T>
class CSVLogger;

typedef boost::shared_ptr<FootForceController> FootForceControllerPtr;
typedef boost::shared_ptr<FootTorqueController> FootTorqueControllerPtr;
typedef boost::shared_ptr<ChestPostureController> ChestPostureControllerPtr;
typedef boost::shared_ptr<ForceDistributor> ForceDistributorPtr;
typedef boost::shared_ptr<ForceSensor> ForceSensorPtr;
typedef boost::shared_ptr<ReferenceIK> ReferenceIKPtr;

class Stabilizer : public TrajectoryController
{
public:
    Stabilizer(SimDynamics::DynamicsRobotPtr robot,
               const ForceSensorPtr& leftAnkleSensor,
               const ForceSensorPtr& rightAnkleSensor,
               const std::string& motionPath,
               const std::string& goalMotionName);

    const Eigen::Matrix4f& getChestPose() { return chestPose; }
    const Eigen::Matrix4f& getPelvisPose() { return pelvisPose; }
    const Eigen::Matrix4f& getLeftFootPose() { return leftFootPose; }
    const Eigen::Matrix4f& getRightFootPose() { return rightFootPose; }
    const Eigen::VectorXf& getResultAngles() { return resultAngles; }
    const Eigen::Matrix4f& getRootPose() { return rootPose; }

    virtual void enableLogging(const std::string& path);

protected:
    virtual void control(float dt) override;
    virtual void log(float dt) override;

private:
    void adaptFrame(Eigen::Matrix4f& frame);

    // needs to be affected by torso rotation + orientation
    VirtualRobot::RobotNodePtr chest;
    // should not be affected by torso rotation + orientation, only changes in leg angles
    VirtualRobot::RobotNodePtr pelvis;
    // TCP on left foot
    VirtualRobot::RobotNodePtr leftAnkle;
    // TCP on right foot
    VirtualRobot::RobotNodePtr rightAnkle;
    // joint + body of left foot
    VirtualRobot::RobotNodePtr leftFoot;
    // joint + body of right foot
    VirtualRobot::RobotNodePtr rightFoot;
    // all nodes that are used for the IK
    VirtualRobot::RobotNodeSetPtr nodes;

    boost::shared_ptr<CSVLogger<double>> logger;

    FootForceControllerPtr    footForceController;
    FootTorqueControllerPtr   footTorqueController;
    ChestPostureControllerPtr chestPostureController;
    ForceDistributorPtr       forceDistributor;
    ForceSensorPtr            leftAnkleSensor;
    ForceSensorPtr            rightAnkleSensor;
    ReferenceIKPtr            referenceIK;

    std::vector<VirtualRobot::RobotNodePtr> trajectoryNodes;

    Eigen::Matrix4f chestPose;
    Eigen::Matrix4f pelvisPose;
    Eigen::Matrix4f leftFootPose;
    Eigen::Matrix4f rightFootPose;
    Eigen::Matrix4f rootPose;
    Eigen::VectorXf resultAngles;
};

typedef boost::shared_ptr<Stabilizer> StabilizerPtr;

#endif
