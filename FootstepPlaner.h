#ifndef __Footstep_Planer_H_
#define __Footstep_Planer_H_

#include <VirtualRobot/VirtualRobot.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoSwitch.h>
#include <Inventor/nodes/SoMaterial.h>

#define EIGEN_DONT_ALIGN_STATICALLY

class FootstepPlaner
{
public:
	FootstepPlaner();
	~FootstepPlaner();

	virtual void generate(int numberOfSteps=5) = 0;
	
	void setRobotModel(VirtualRobot::RobotPtr pRobot, 
		std::string nameRightFoot = "RightLeg_BodyAnkle2", std::string nameLeftFoot = "LeftLeg_BodyAnkle2");

	SoSeparator* getVisualization();

	void showFootPositions(bool isVisible);
	void showFootTrajectories(bool isVisible);

	Eigen::Matrix3Xf const getLeftFootPositions() {return _mLFootPositions;};
	Eigen::Matrix3Xf const getRightFootPositions() {return _mRFootPositions;};
	static void writeSceneGraphToFile(SoSeparator* node);

protected:
	void computeFeetShape();
	void buildVisualization();
	static void generateVisualizationDuplicatesFromTrajectories(SoSeparator* whereToInsert, 
		SoSeparator* whatToInsert, Eigen::Matrix3Xf &whereToTranslate);

	// data structures to save footstep positions and feet trajectories
	Eigen::Matrix3Xf _mLFootTrajectory;
	Eigen::Matrix3Xf _mRFootTrajectory;
	Eigen::Matrix3Xf _mLFootPositions;
	Eigen::Matrix3Xf _mRFootPositions;

	// administrative bool values
	bool _bChangesMade;
	bool _bGenerated;
	
	// the robot model and the names of the foot segments
	VirtualRobot::RobotPtr _pRobot;
	std::string _sLeftFootName;
	std::string _sRightFootName;

	// starting points of robot, right-foot and left-foot
	Eigen::Vector2f _vRobotCenter;
	Eigen::Vector2f _vRightFootCenter;
	Eigen::Vector2f _vLeftFootCenter;

	// starting point of generated trajectories
	Eigen::Vector3f _vDeltaRightFoot;
	Eigen::Vector3f _vDeltaLeftFoot;

	// rotation for walking in the right direction
	Eigen::Matrix2f _mRotateWalking;

	// ** visualization nodes **
	// visualization for the right foot (with border), without border, feet position and feet trajectory
	SoSeparator* _visuRightFoot;
	SoSeparator* _visuRightFootwoBorder;
	SoSeparator* _visuRightFootPositions;
	SoSeparator* _visuRightFootTrajectory;
	// visualization for the left foot (with border), without border, feet position and feet trajectory
	SoSeparator* _visuLeftFoot;
	SoSeparator* _visuLeftFootwoBorder;
	SoSeparator* _visuLeftFootPositions;
	SoSeparator* _visuLeftFootTrajectory;
	// root node for visualization
	SoSeparator* _visualization;
	// switches to enable or disable visualization of footstep positions and foot trajectories
	SoSwitch* _swPositions;
	SoSwitch* _swTrajectories;
};

#endif
