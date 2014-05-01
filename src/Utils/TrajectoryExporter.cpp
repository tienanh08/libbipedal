#include <fstream>
#include <string>
#include <sstream>

#include <Eigen/Dense>

#include <VirtualRobot/VirtualRobot.h>
#include <VirtualRobot/Robot.h>
#include <VirtualRobot/RobotNodeSet.h>
#include <VirtualRobot/Nodes/RobotNode.h>

#include <MMM/Motion/Motion.h>
#include <MMM/XMLTools.h>

#include <boost/filesystem.hpp>

#include "TrajectoryExporter.h"
#include "VelocityEstimation.h"

void TrajectoryExporter::exportToMMM(const std::string& path)
{
    VirtualRobot::RobotNodeSetPtr nodeSet = robot->getRobotNodeSet("Left2RightLeg");
	Eigen::Matrix4f rootPose = nodeSet->getKinematicRoot()->getGlobalPose();

	boost::filesystem::path targetPath(path);
	boost::filesystem::path baseDir = targetPath.parent_path();
	std::string relRobotPath = MMM::XML::make_relative(baseDir.string(), pathToRobot);

	MMM::MotionPtr motion(new MMM::Motion("Walking pattern"));

	std::vector<std::string> jointNames;
	for(int i = 0; i < nodeSet->getSize(); i++)
		jointNames.push_back((*nodeSet)[i]->getName());
	
	motion->setJointOrder(jointNames);

	int size = bodyTrajectory.cols();
	int ndof = bodyTrajectory.rows();

	Eigen::MatrixXf bodyVelocity = VelocityEstimation::neighboursDiff(bodyTrajectory, timestep);

	for (int i = 0; i < size; i++)
	{
		// we need rootPos in mm
		Eigen::Vector3f rootPos = 1000 * leftFootTrajectory.col(i);
		MMM::MotionFramePtr frame(new MMM::MotionFrame(ndof));
		frame->setRootPose(rootPose);
		frame->setRootPos(rootPos);
		frame->joint = bodyTrajectory.col(i);
		frame->joint_vel = bodyVelocity.col(i);
		frame->timestep = timestep*i;
		motion->addMotionFrame(frame);
	}

	MMM::ModelPtr model(new MMM::Model());
	model->filename = relRobotPath;
	motion->setModel(model);

	std::ofstream out(path.c_str());
	out << "<MMM>"
	<< motion->toXML()
	<< "</MMM>";
}
