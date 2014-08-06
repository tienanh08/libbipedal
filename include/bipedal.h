#ifndef __BIPEDAL_H__
#define __BIPEDAL_H__

#include <Eigen/Dense>
#include <boost/shared_ptr.hpp>

namespace Kinematics {
    enum SupportPhase : unsigned short;
};

class PolynominalFootstepPlaner;
class ZMPPreviewControl;
class FootstepPlaner;
class ZMPPlaner;
class TrajectoryPlayer;
class TrajectoryExporter;
class ReferenceIK;
class KajitaStabilizer;
template<typename T> class ControlMatrixEntry;
template<typename T> class ControlMatrixParser;
template<typename T> class ControlPointEntry;
template<typename T> class ControlPointParser;
template<typename T> class ControlValueEntry;
template<typename T> class ControlValueParser;

typedef ControlPointEntry<Eigen::Vector2f>   ControlPointEntry2f;
typedef ControlPointParser<Eigen::Vector2f>  ControlPointParser2f;
typedef ControlPointEntry<Eigen::Vector3f>   ControlPointEntry3f;
typedef ControlPointParser<Eigen::Vector3f>  ControlPointParser3f;
typedef ControlMatrixEntry<Eigen::Matrix4f>  ControlMatrixEntry4f;
typedef ControlMatrixParser<Eigen::Matrix4f> ControlMatrixParser4f;

typedef boost::shared_ptr<KajitaStabilizer>          KajitaStabilizerPtr;
typedef boost::shared_ptr<TrajectoryPlayer>          TrajectoryPlayerPtr;
typedef boost::shared_ptr<TrajectoryExporter>        TrajectoryExporterPtr;
typedef boost::shared_ptr<ReferenceIK>               ReferenceIKPtr;
typedef boost::shared_ptr<FootstepPlaner>            FootstepPlanerPtr;
typedef boost::shared_ptr<ZMPPlaner>                 ZMPPlanerPtr;
typedef boost::shared_ptr<PolynominalFootstepPlaner> PolynominalFootstepPlanerPtr;
typedef boost::shared_ptr<ZMPPreviewControl>         ZMPPreviewControlPtr;

#endif