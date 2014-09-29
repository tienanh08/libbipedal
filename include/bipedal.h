#ifndef __BIPEDAL_H__
#define __BIPEDAL_H__

#include <Eigen/Dense>
#include <boost/shared_ptr.hpp>

namespace Eigen {
    typedef Matrix<float, 6, Dynamic> Matrix6Xf;
    typedef Matrix<float, 6, 1> Vector6f;
};

namespace Bipedal {

enum SupportPhase : unsigned short;

template<bool, bool, bool> class PostureController;
using TwoDOFPostureController = PostureController<true, true, false>;
using ThreeDOFPostureController = PostureController<true, true, true>;

class PushRecovery;
class CapturePointRecovery;
class ZMPPlaner;
class ZMPReferencePlaner;
class ZMPPreviewControl;
class WalkingIK;
class HierarchicalWalkingIK;
class TrajectoryLogger;
class TorqueControllingStabilizer;
class StabilizerFactory;
class CartesianStabilizer;
class FrameAdaptingStabilizer;
class PolynominalFootstepPlaner;
class ZMPPreviewControl;
class FootstepPlaner;
class ZMPPlaner;
class TrajectoryPlayer;
class TrajectoryExporter;
class ReferenceIK;
class KajitaStabilizer;
class DampeningController;
class MultiBodyZMPEstimator;
template<typename T> class ControlMatrixEntry;
template<typename T> class ControlMatrixParser;
template<typename T> class ControlPointEntry;
template<typename T> class ControlPointParser;
template<typename T> class ControlValueEntry;
template<typename T> class ControlValueParser;

template<typename T> class CubivBezierCurve;
typedef CubivBezierCurve<Eigen::Vector3f> CubicBezierCurve3f;
typedef CubivBezierCurve<Eigen::Vector2f> CubicBezierCurve2f;

template<typename T, unsigned order> class BackwardDerivationEstimator;
template<typename T> using DerivationEstimator = BackwardDerivationEstimator<T, 1>;
template<typename T> using ThirdOrderBackwardDerivationEstimator = BackwardDerivationEstimator<T, 3>;
template<typename T> using SixthOrderBackwardDerivationEstimator = BackwardDerivationEstimator<T, 6>;

typedef ControlPointEntry<Eigen::Vector2f>   ControlPointEntry2f;
typedef ControlPointParser<Eigen::Vector2f>  ControlPointParser2f;
typedef ControlPointEntry<Eigen::Vector3f>   ControlPointEntry3f;
typedef ControlPointParser<Eigen::Vector3f>  ControlPointParser3f;
typedef ControlMatrixEntry<Eigen::Matrix4f>  ControlMatrixEntry4f;
typedef ControlMatrixParser<Eigen::Matrix4f> ControlMatrixParser4f;

typedef boost::shared_ptr<PushRecovery>                PushRecoveryPtr;
typedef boost::shared_ptr<CapturePointRecovery>        CapturePointRecoveryPtr;
typedef boost::shared_ptr<WalkingIK>                   WalkingIKPtr;
typedef boost::shared_ptr<HierarchicalWalkingIK>       HierarchicalWalkingIKPtr;
typedef boost::shared_ptr<TorqueControllingStabilizer> TorqueControllingStabilizerPtr;
typedef boost::shared_ptr<StabilizerFactory>           StabilizerFactoryPtr;
typedef boost::shared_ptr<FrameAdaptingStabilizer>     FrameAdaptingStabilizerPtr;
typedef boost::shared_ptr<KajitaStabilizer>            KajitaStabilizerPtr;
typedef boost::shared_ptr<CartesianStabilizer>         CartesianStabilizerPtr;
typedef boost::shared_ptr<TrajectoryPlayer>            TrajectoryPlayerPtr;
typedef boost::shared_ptr<TrajectoryExporter>          TrajectoryExporterPtr;
typedef boost::shared_ptr<TrajectoryLogger>            TrajectoryLoggerPtr;
typedef boost::shared_ptr<ReferenceIK>                 ReferenceIKPtr;
typedef boost::shared_ptr<FootstepPlaner>              FootstepPlanerPtr;
typedef boost::shared_ptr<ZMPPlaner>                   ZMPPlanerPtr;
typedef boost::shared_ptr<PolynominalFootstepPlaner>   PolynominalFootstepPlanerPtr;
typedef boost::shared_ptr<ZMPPreviewControl>           ZMPPreviewControlPtr;
typedef boost::shared_ptr<TwoDOFPostureController>     TwoDOFPostureControllerPtr;
typedef boost::shared_ptr<ThreeDOFPostureController>   ThreeDOFPostureControllerPtr;
typedef boost::shared_ptr<ZMPPlaner>                   ZMPPlanerPtr;
typedef boost::shared_ptr<ZMPReferencePlaner>          ZMPReferencePlanerPtr;
typedef boost::shared_ptr<ZMPPreviewControl>           ZMPPreviewControlPtr;
typedef boost::shared_ptr<MultiBodyZMPEstimator>       MultiBodyZMPEstimatorPtr;

}

#endif
