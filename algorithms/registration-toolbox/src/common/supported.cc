#include "registration-toolbox/common/supported.h"

#include <glog/logging.h>

namespace regbox {

std::string SupportedAligner::getKeyForAligner(Aligner aligner) {
  if (aligner == Aligner::PclIcp) {
    return "regbox::PclIcpController";
  } else if (aligner == Aligner::PclGIcp) {
    return "regbox::PclGeneralizedIcpController";
  } else if (aligner == Aligner::PclVGIcp) {
    return "regbox::PclVoxelizedGeneralizedIcpController";
  } else if (aligner == Aligner::Mock) {
    return "regbox::MockController";
  } else if (aligner == Aligner::LpmIcp) {
    return "regbox::LpmIcpController";
  } else if (aligner == Aligner::Loam) {
    return "regbox::LoamController";
  } else {
    LOG(FATAL) << "Unsupported alignment type given: "
               << static_cast<int>(aligner);
    return "";
  }
}

}  // namespace regbox
